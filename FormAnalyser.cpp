#include "FormAnalyser.h"
#include "IconMatchingException.h"
#include <time.h>
#include "Logger.h"
#include <math.h>
#include <algorithm>

FormAnalyser::FormAnalyser(const std::map<std::string, Icon*>& iconList, const BaseForm& baseForm) {
	m_iconList = iconList;
	m_baseForm = baseForm;

	m_crossTemplate = cv::imread("images/templates/cross.png");
	cv::cvtColor(m_crossTemplate, m_crossTemplate, CV_RGB2GRAY);
}

void FormAnalyser::analyse(std::string formPath) {
	Logger() << "Analysing " << formPath;
	clock_t beginTime = clock();

	currentImage = formPath.substr(27,5);

	// Extracting the image matrix
	m_form = cv::imread(formPath);

	// Converting the RGB image into a gray one to increase the process speed
	cv::cvtColor(m_form, m_workingForm, CV_RGB2GRAY);

	// Retrieving the cross position
	getSupCross();
	getSubCross();
	Logger() << "Crosses position determined";
	
	// Rotating, scaling and cropping image
	adjustAngle();
	resize();
	reposition();

	// Converting the RGB image into a gray one to increase the process speed
	cv::cvtColor(m_form, m_workingForm, CV_RGB2GRAY);

	// converting RGB templates images into gray image
	setUpTemplates();
	
	// extracting every lines and icon boxes
	handleLines();

	Logger() << "Analysing time: " << (clock() - beginTime)  << " ms\n";
}


void FormAnalyser::getSupCross() {
	cv::Mat result;

	// Extracting top right corner
	cv::Mat subMat = m_workingForm(cv::Rect(m_workingForm.cols/2, 0, m_workingForm.cols/2, m_workingForm.rows/4));

	// Seeking top cross
	cv::matchTemplate(subMat, m_crossTemplate, result, CV_TM_CCORR_NORMED);
	minMaxLoc(result, NULL, NULL, NULL, &m_crossSupPosition);

	// Adjusting cross coordinates
	m_crossSupPosition.x += 63 + m_workingForm.cols/2;
	m_crossSupPosition.y += 58;
}


void FormAnalyser::getSubCross() {
	cv::Mat result;

	// Extracting bottom left corner
	cv::Mat subMat = m_workingForm(cv::Rect(0, 2*m_workingForm.rows/3, m_workingForm.cols/3, m_workingForm.rows/3));

	// Seeking sub cross
	cv::matchTemplate(subMat, m_crossTemplate, result, CV_TM_CCORR_NORMED);
	minMaxLoc(result, NULL, NULL, NULL, &m_crossSubPosition);

	// Adjusting cross coordinates
	m_crossSubPosition.x += 63;
	m_crossSubPosition.y += 58 + 2*m_workingForm.rows/3;
}


void FormAnalyser::setUpTemplates() {
	std::map<std::string, Icon*>::iterator it,end;
	cv::Mat temp;

	end = m_iconList.end();
	for(it=m_iconList.begin();it!=end;it++) {
		temp = cv::imread(it->second->getTemplatePath());
		cv::cvtColor(temp, temp, CV_RGB2GRAY);
		m_iconMatList[it->first] = temp;
	}
}


void FormAnalyser::reposition() {
	int deltaX, deltaY, roiX, roiY, roiW, roiH, formX, formY;

	deltaX = m_baseForm.getTopCrossPosition().x-static_cast<int>(m_crossSupPosition.x);
	deltaY = m_baseForm.getTopCrossPosition().y-static_cast<int>(m_crossSupPosition.y);

	if(deltaX<0) {
		roiX = -deltaX;
		formX = 0;
		
	} else {
		roiX = 0;
		formX = deltaX;
	}

	if(deltaY<0) {
		roiY = -deltaY;
		formY = 0;
		
	} else {
		roiY = 0;
		formY = deltaY;
	}

	roiW = std::min(m_baseForm.getFormWidth(),m_form.cols-roiX)-formX;
	roiH = std::min(m_baseForm.getFormHeight(),m_form.rows-roiY)-formY;
	
	// selecting the RO
	cv::Mat temp = m_form(cv::Rect(roiX, roiY, roiW, roiH));

	// copying ROI in the final image
	cv::Mat final(m_baseForm.getFormHeight(), m_baseForm.getFormWidth(), m_form.type());
	temp.copyTo(final(cv::Rect(formX, formY, roiW, roiH)));
    m_form = final;

	Logger() << "Image cropped.";
}

void FormAnalyser::adjustAngle() {
	double angle,angle1;

	angle = atan2(static_cast<double>(m_baseForm.getTopCrossPosition().y-m_baseForm.getBottomCrossPosition().y), static_cast<double>(m_baseForm.getTopCrossPosition().x - m_baseForm.getBottomCrossPosition().x));
    angle1 = atan2(static_cast<double>(m_crossSupPosition.y - m_crossSubPosition.y), static_cast<double>(m_crossSupPosition.x - m_crossSubPosition.x));
	angle = (angle1-angle);

	cv::Point src_center(m_crossSupPosition.x, m_crossSupPosition.y);

	//finding bounding rectangle after rotation
	double x1, y1, x2, y2, x3, y3, x4, y4;
	int maxW,maxH,deltaX,deltaY;

	x1 = 0-src_center.x;
	y1 = 0-src_center.y;
	x1 = x1*cos(angle) - y1*sin(angle);
	y1 = x1*sin(angle) + y1*cos(angle);
	x1 += src_center.x;
	y1 += src_center.y;

	x2 = m_form.cols-src_center.x;
	y2 = 0-src_center.y;
	x2 = x2*cos(angle) - y2*sin(angle);
	y2 = x2*sin(angle) + y2*cos(angle);
	x2 += src_center.x;
	y2 += src_center.y;

	x3 = m_form.cols-src_center.x;
	y3 = m_form.rows-src_center.y;
	x3 = x3*cos(angle) - y3*sin(angle);
	y3 = x3*sin(angle) + y3*cos(angle);
	x3 += src_center.x;
	y3 += src_center.y;

	x4 = 0-src_center.x;
	y4 = m_form.rows-src_center.y;
	x4 = x4*cos(angle) - y4*sin(angle);
	y4 = x4*sin(angle) + y4*cos(angle);
	x4 += src_center.x;
	y4 += src_center.y;

	//finding extreme values:
	maxW = static_cast<int>(std::max(abs(x1-x3),abs(x2-x4)));
	maxW = static_cast<int>(std::max(maxW, m_form.cols));
	maxH = static_cast<int>(std::max(abs(y1-y3),abs(y2-y4)));
	maxH = static_cast<int>(std::max(maxH, m_form.rows));

	deltaX = abs((m_form.cols-maxW)/2);
	deltaY = abs((m_form.rows-maxH)/2);

	//resizing zone
	cv::Mat tmp(maxH, maxW, m_form.type());
    m_form.copyTo(tmp(cv::Rect((maxW-m_form.cols)/2, (maxH-m_form.rows)/2, m_form.cols, m_form.rows)));
	src_center.x += (maxW-m_form.cols)/2;
	src_center.y += (maxH-m_form.rows)/2;

	// updating top cross position
	m_crossSupPosition.x += (maxW-m_form.cols)/2;
	m_crossSupPosition.y += (maxH-m_form.rows)/2;

	m_form = tmp;

    cv::Mat rot_mat = getRotationMatrix2D(src_center, angle*180/CV_PI, 1.0);
    cv::warpAffine(m_form, m_form, rot_mat, m_form.size());

	// updating bottom cross position
	cv::cvtColor(m_form, m_workingForm, CV_RGB2GRAY);
	getSubCross();

	Logger() << "Image rotated by " << angle*180/CV_PI << " degree";
}

void FormAnalyser::resize() {
	double dist1, dist2, ratio;

	dist1 = sqrt(static_cast<double>((m_crossSupPosition.x-m_crossSubPosition.x)*(m_crossSupPosition.x-m_crossSubPosition.x) + (m_crossSupPosition.y-m_crossSubPosition.y)*(m_crossSupPosition.y-m_crossSubPosition.y)));
	dist2 = sqrt(static_cast<double>((m_baseForm.getTopCrossPosition().x-m_baseForm.getBottomCrossPosition().x)*(m_baseForm.getTopCrossPosition().x-m_baseForm.getBottomCrossPosition().x) + (m_baseForm.getTopCrossPosition().y-m_baseForm.getBottomCrossPosition().y)*(m_baseForm.getTopCrossPosition().y-m_baseForm.getBottomCrossPosition().y)));
	ratio = dist2 / dist1;

	cv::Size s = m_form.size();
	cv::Size s2 = cv::Size(static_cast<int>(s.width*ratio), static_cast<int>(s.height*ratio));
	cv::resize(m_form, m_form, s2);

	// updating top cross position
	m_crossSupPosition.x = static_cast<int>(m_crossSupPosition.x*ratio);
	m_crossSupPosition.y = static_cast<int>(m_crossSupPosition.y*ratio);

	// updating bottom cross position
	m_crossSubPosition.x = static_cast<int>(m_crossSubPosition.x*ratio);
	m_crossSubPosition.y = static_cast<int>(m_crossSubPosition.y*ratio);

	Logger() << "Image resized with a ratio of " << ratio;
}

void FormAnalyser::handleLines() {
	BaseFormLine* line;
	int numLine, numBox;
	std::string currentClass;

	numLine = m_baseForm.getLineNumber();
	for(int i=0; i<numLine; i++) {
		line = m_baseForm.getLine(i);

		try{
			currentClass = findIcon(line->getIconPosition());
			Logger() << "Current line class: " << currentClass;

			numBox = line->getBoxNumber();
			for(int j=0;j<numBox;j++) {
				saveBoxContent(currentClass, line->getBoxPosition(j), i, j);
			}
		} catch(const IconMatchingException& e) {
			Logger() << "Couldn't find the icon class of the line " << i << ". Matching confidence too low: " << e.getConfidence();
		}
	}
}

void FormAnalyser::saveBoxContent(std::string iconClass, cv::Point position, int i, int j) {
	std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(4);

	std::stringstream ss;
	ss << "images/temp/" << iconClass << "/" << currentImage << "_" << i << "_" << j << ".png";
	cv::imwrite(ss.str() ,m_form(cv::Rect(position.x, position.y, m_baseForm.getBoxWidth(), m_baseForm.getBoxHeight())), compression_params);
}

const std::string& FormAnalyser::findIcon(const cv::Point& roi) {
	cv::Mat result;

	// Extracting ROI
	cv::Mat subMat = m_workingForm(cv::Rect(roi.x, roi.y, m_baseForm.getIconROIWidth(), m_baseForm.getIconROIHeight()));

	double currentVal,maxVal;
	std::map<std::string, cv::Mat>::iterator it, end, res;

	end = m_iconMatList.end();
	maxVal = -1;
	res = end;

	// trying to match a icon class
	for(it=m_iconMatList.begin();it!=end;it++) {
		matchTemplate(subMat, it->second, result, CV_TM_CCOEFF_NORMED);
		minMaxLoc (result, NULL, &currentVal, NULL, NULL);

		if(currentVal>maxVal) {
			maxVal = currentVal;
			res = it;
			//if(currentVal>0.9) break;
		}
	}
	if(maxVal <= 0.5) {
		throw IconMatchingException(maxVal);
	}
	return res->first;
}