#include "FeatureExtractor.h"

#include <sstream>
#include <iomanip>
#include <regex>
#include <omp.h>

#include <opencv2\opencv.hpp>

#include "Logger.h"

const std::string SINGLE_FILE = "single_file";


FeatureExtractor::FeatureExtractor(const std::string& outputFolder, const std::string& relationName, const std::map<std::string, Icon*>& iconList, int normalizedWidth, int normalizedHeight)
	: _outputFolder(outputFolder), _relationName(relationName), _iconList(iconList), _normalizedWidth(normalizedWidth), _normalizedHeight(normalizedHeight)
{
	_seperateFile = false;
	_mode = INPUT_FILE;
	_hasStarted = false;
	_fileName = "features";
}

FeatureExtractor::~FeatureExtractor()
{
	for(std::vector<Feature*>::iterator it = _featureList.begin(); it!=_featureList.end(); ++it)  {
		delete *it;
	}

	/*for(std::map<std::string, Icon* >::iterator mapIt = _iconList.begin(); mapIt != _iconList.end(); ++mapIt) {
		delete mapIt->second;
	}*/
}

void FeatureExtractor::save() {
	for(std::map<std::string, std::ofstream>::iterator it = _outputStream.begin(); it != _outputStream.end(); ++it) {
		it->second.flush();
		it->second.close();
	}

	_hasStarted = false;
}

void FeatureExtractor::addFeature(Feature* feature) 
{
	_featureList.push_back(feature);
}

void FeatureExtractor::extract(const std::string& sourceFolder, const std::string& xmlImageList)
{
	Logger(omp_get_thread_num(),true) << "Extracting image list from " << xmlImageList;
	initFileStream(xmlImageList);

	_parser.parse(xmlImageList.c_str());

	std::map<std::string, std::vector<std::string> > fileList = _parser.getFileList();

	std::string currentStream;

	bool isClassListEmpty = _classList.empty();

	for(std::map<std::string, std::vector<std::string> >::iterator mapIt = fileList.begin(); mapIt != fileList.end(); ++mapIt) {
		
		if(isClassListEmpty || std::find(_classList.begin(), _classList.end(), mapIt->first)!=_classList.end()) {

			if(_seperateFile) {
				if(_mode == ICON) {
					currentStream = mapIt->first;
				} else {
					currentStream = xmlImageList;
				}
			} else {
				currentStream = SINGLE_FILE;
			}

			for(std::vector<std::string>::iterator fileIt = mapIt->second.begin(); fileIt != mapIt->second.end(); ++fileIt) {
				cv::Mat imageRaw = cv::imread(sourceFolder+*fileIt);
				cv::Mat imageNorm;
				cv::Mat imageNormBin;
				cv::Rect boundingBox = normalize(imageRaw, imageNorm, _normalizedWidth, _normalizedHeight);
				binariseImage(imageNorm, imageNormBin);
				removeNoise(imageNormBin, imageNormBin);

				for(std::vector<Feature*>::iterator it = _featureList.begin(); it!=_featureList.end(); ++it)  {

					std::vector<double> res = (*it)->execute(imageRaw, imageNorm, imageNormBin, boundingBox);

					for(std::vector<double>::iterator itValues = res.begin(); itValues!=res.end(); ++itValues) {
						_outputStream[currentStream] << *itValues << ",";
					}
				}

				_outputStream[currentStream] << mapIt->first << "\n";
			}

			_outputStream[currentStream].flush();
		}
	}
}

void FeatureExtractor::initFileStream(const std::string& xmlFile) {
	if(_seperateFile) {
		if(_mode == INPUT_FILE) {
			std::smatch m;
			std::regex e (".*/(.*?)\\..*?");
			std::regex_match (xmlFile, m, e);

			std::stringstream ss;
			ss << _outputFolder << *(++m.begin()) << ".arff";
			Logger(omp_get_thread_num(),true) << "Creating ARFF file: " << ss.str();
			_outputStream[xmlFile] = std::ofstream(ss.str(), std::ios_base::out | std::ios_base::trunc);
			setARFFHeaders(_outputStream[xmlFile]);
		} else if(!_hasStarted){
			std::stringstream ss;
			if(_classList.empty()) {
				for(std::map<std::string, Icon*>::iterator it = _iconList.begin(); it != _iconList.end(); ++it) {
					ss.str("");
					ss << _outputFolder << "features-" << it->first << ".arff";
					Logger(omp_get_thread_num(),true) << "Creating ARFF file: " << ss.str();
					_outputStream[it->first] = std::ofstream(ss.str(), std::ios_base::out | std::ios_base::trunc);
					setARFFHeaders(_outputStream[it->first]);
				}
			} else {
				for(std::vector<std::string>::iterator it = _classList.begin(); it!=_classList.end(); ++it) {
					ss.str("");
					ss << _outputFolder << "features-" << *it << ".arff";
					Logger(omp_get_thread_num(),true) << "Creating ARFF file: " << ss.str();
					_outputStream[*it] = std::ofstream(ss.str(), std::ios_base::out | std::ios_base::trunc);
					setARFFHeaders(_outputStream[*it]);
				}
			}
			_hasStarted = true;
		}
	} else if(!_hasStarted){
		std::stringstream ss;
		ss << _outputFolder << _fileName << ".arff";
		Logger(omp_get_thread_num(),true) << "Creating ARFF file: " << ss.str();
		_outputStream[SINGLE_FILE] = std::ofstream(ss.str(), std::ios_base::out | std::ios_base::trunc);
		setARFFHeaders(_outputStream[SINGLE_FILE]);
		_hasStarted = true;
	}
}


void FeatureExtractor::setARFFHeaders(std::ofstream& stream) {
	stream << "@relation " << _relationName << "\n\n";
	int nbZone;

	std::map<std::string, int> featureList;
	for(std::vector<Feature*>::iterator it = _featureList.begin(); it!=_featureList.end(); ++it) {
		featureList[(*it)->featureNames()[0]] = 0;
	}

	for(std::vector<Feature*>::iterator it = _featureList.begin(); it!=_featureList.end(); ++it) {
		std::vector<std::string> names = (*it)->featureNames();

		nbZone = (*it)->getNbZone();
		if(nbZone==1) {
			for(std::vector<std::string>::iterator itName = names.begin(); itName!=names.end(); ++itName) {
					stream << "@attribute " << *itName << featureList[names[0]] << " REAL\n";
			}
		} else {
			for(int i=0;i<(*it)->getNbZone();++i) {
				for(std::vector<std::string>::iterator itName = names.begin(); itName!=names.end(); ++itName) {
					stream << "@attribute " << *itName << featureList[names[0]] << "_" << i << " REAL\n";
				}
			}
		}

		featureList[names[0]]++;
	}

	stream << "@attribute " << "class {";
	std::map<std::string, Icon*>::iterator it = _iconList.begin();
	stream << it->first;
	for(++it; it != _iconList.end(); ++it) {
		stream << "," << it->first;
	}

	stream << "}\n\n";
	
	stream << "@data\n";
}

cv::Rect FeatureExtractor::normalize(const cv::Mat& src, cv::Mat& dst, int normW, int normH) {
	cv::Mat bin;
	binariseImage(src, bin);
	removeNoise(bin, bin);

	cv::Rect boundingBox = getBoundingBox(bin);
	dst = src(boundingBox);

	const int space = 0;

	cv::Mat tmp(normH, normW, src.type(), cv::Scalar(255,255,255));
	if(boundingBox.width > boundingBox.height) {

		int height = boundingBox.height*(normW-2*space)/boundingBox.width;
		cv::resize(dst, dst, cv::Size(normW-2*space, height));
		dst.copyTo(tmp(cv::Rect(space, (normH-height)/2+space, dst.cols, dst.rows)));

	} else if(boundingBox.width < boundingBox.height){

		int width = boundingBox.width*(normH-2*space)/boundingBox.height;
		cv::resize(dst, dst, cv::Size(width, normH-2*space));
		dst.copyTo(tmp(cv::Rect((normW-width)/2+space, space, dst.cols, dst.rows)));

	} else {

		cv::resize(dst, dst, cv::Size(normW-2*space, normH-2*space));
		dst.copyTo(tmp(cv::Rect(space, space, dst.cols, dst.rows)));
	}
	dst = tmp;

	return boundingBox;
}

void FeatureExtractor::binariseImage(const cv::Mat& src, cv::Mat& dst) {
	cv::cvtColor(src, dst, CV_RGB2GRAY);
	//cv::blur(dst, dst, cv::Size(3,3));
	dst = dst < 254;
}

void FeatureExtractor::removeNoise(const cv::Mat& src, cv::Mat& dst) {
	cv::Mat elt = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5), cv::Point(2, 2));
	//cv::morphologyEx(src, dst, cv::MORPH_CLOSE, elt);
	cv::morphologyEx(dst, dst, cv::MORPH_OPEN, elt);
}

cv::Rect FeatureExtractor::getBoundingBox(const cv::Mat& src) {
	unsigned char *input = (unsigned char*)(src.data);

	bool stop;
	int topY = 0, bottomY = _normalizedHeight, leftX = 0, rightX = _normalizedWidth;
	
	stop = false;
	for(int i=0; i<src.rows&&!stop; ++i) {
		for(int j=0; j<src.cols&&!stop; ++j) {
			if(input[src.step*j+i]!=0) {
				leftX = i;
				stop = true;
			}
		}
	}

	stop = false;
	for(int i=0; i<src.cols&&!stop; ++i) {
		for(int j=0; j<src.rows&&!stop; ++j) {
			if(input[src.step*i+j]!=0) {
				topY = i;
				stop = true;
			}
		}
	}

	stop = false;
	for(int i=src.cols-1;i>=0&&!stop; --i) {
		for(int j=src.rows-1; j>=0&&!stop; --j) {
			if(input[src.step*i+j]!=0) {
				bottomY = i;
				stop = true;
			}
		}
	}

	stop = false;
	for(int i=src.rows-1;i>=0&&!stop; --i) {
		for(int j=src.cols-1; j>=0&&!stop; --j) {
			if(input[src.step*j+i]!=0) {
				rightX = i;
				stop = true;
			}
		}
	}

	return cv::Rect(leftX, topY, (rightX-leftX), (bottomY-topY));
}