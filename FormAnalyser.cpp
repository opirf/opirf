#include "FormAnalyser.h"
#include <time.h>
#include "Logger.h"

FormAnalyser::FormAnalyser(const std::map<std::string, Icon*>& iconList, const BaseForm& baseForm) {
	m_iconList = iconList;
	m_baseForm = baseForm;

	m_crossTemplate = cv::imread("images/templates/cross.png");
	cv::cvtColor(m_crossTemplate, m_crossTemplate, CV_RGB2GRAY);
}

void FormAnalyser::analyse(std::string formPath) {
	Logger() << "Analysing " << formPath;
	clock_t beginTime = clock();

	// Extracting the image matrix
	m_form = cv::imread(formPath);
	// Converting the RGB image into a gray one to increase the process speed
	cv::cvtColor(m_form, m_workingForm, CV_RGB2GRAY);

	// Retrieving the cross position
	getSupCross();
	Logger() << "Top cross position: (" << m_crossSupPosition.x << "," << m_crossSupPosition.y << ")";
	getSubCross();
	Logger() << "Bottom cross position: (" << m_crossSupPosition.x << "," << m_crossSupPosition.y << ")";

	setUpTemplates();
	
	handleLines();

	Logger() << "Analysing time: " << (clock() - beginTime)  << " ms";
}


void FormAnalyser::getSupCross() {
	cv::Mat result;

	// Extracting top right corner
	cv::Mat subMat = m_workingForm(cv::Rect(m_workingForm.cols/2, 0, m_workingForm.cols/2, m_workingForm.rows/3));

	// Seeking top cross
	cv::matchTemplate(subMat, m_crossTemplate, result, CV_TM_CCOEFF_NORMED);
	minMaxLoc(result, NULL, NULL, NULL, &m_crossSupPosition);

	// Adjusting cross coordinates
	m_crossSupPosition.x += 63 + m_workingForm.cols/2;
	m_crossSupPosition.y += 58;
}


void FormAnalyser::getSubCross() {
	cv::Mat result;

	// Extracting bottom left corner
	cv::Mat subMat = m_workingForm(cv::Rect(0, 2*m_workingForm.rows/3, m_workingForm.cols/2, m_workingForm.rows/3));

	// Seeking sub cross
	cv::matchTemplate(subMat, m_crossTemplate, result, CV_TM_CCOEFF_NORMED);
	minMaxLoc(result, NULL, NULL, NULL, &m_crossSupPosition);

	// Adjusting cross coordinates
	m_crossSupPosition.x += 63;
	m_crossSupPosition.y += 58 + 2*m_workingForm.rows/3;
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

void FormAnalyser::handleLines() {
	BaseFormLine* line;
	int numLine, numBox;
	std::string currentClass;

	numLine = m_baseForm.getLineNumber();
	for(int i=0; i<numLine; i++) {
		line = m_baseForm.getLine(i);
		currentClass = findIcon(line->getIconPosition());

		numBox = line->getBoxNumber();
		for(int j=0;j<numBox;j++) {
			saveBoxContent(currentClass, line->getBoxPosition(j), i, j);
		}
	}
}

void FormAnalyser::saveBoxContent(std::string iconClass, cv::Point position, int i, int j) {
	std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

	std::stringstream ss;
	ss << "images/temp/" << iconClass << "/box_" << i << "_" << j << ".png";
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
	res=end;
	for(it=m_iconMatList.begin();it!=end;it++) {
		matchTemplate(subMat, it->second, result, CV_TM_CCOEFF_NORMED);
		minMaxLoc (result, NULL, &currentVal, NULL, NULL);

		if(currentVal>maxVal) {
			maxVal = currentVal;
			res = it;
			//if(currentVal>0.9) break;
		}
	}

	return res->first;
}