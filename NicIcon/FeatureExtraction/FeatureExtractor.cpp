#include "FeatureExtractor.h"

#include <sstream>
#include <iomanip>
#include <regex>

#include <opencv2\opencv.hpp>

#include "Logger.h"

const std::string SINGLE_FILE = "single_file";


FeatureExtractor::FeatureExtractor(const std::string& tnFolder, const std::string& outputFolder, const std::string& relationName, const std::map<std::string, Icon*>& iconList)
	: _tnFolder(tnFolder), _outputFolder(outputFolder), _relationName(relationName), _iconList(iconList)
{
	_seperateFile = false;
	_mode = INPUT_FILE;
	_hasStarted = false;
}

FeatureExtractor::~FeatureExtractor()
{
	for(std::map<std::string, std::ofstream>::iterator it = _outputStream.begin(); it != _outputStream.end(); ++it) {
		it->second.flush();
		it->second.close();
	}

	for(std::vector<Feature*>::iterator it = _featureList.begin(); it!=_featureList.end(); ++it)  {
		delete *it;
	}

	for(std::map<std::string, Icon* >::iterator mapIt = _iconList.begin(); mapIt != _iconList.end(); ++mapIt) {
		delete mapIt->second;
	}
}

void FeatureExtractor::addFeature(Feature* feature) 
{
	_featureList.push_back(feature);
}

void FeatureExtractor::extract(const std::string& xmlFileList)
{
	Logger() << "Extracting " << xmlFileList;
	initFileStream(xmlFileList);

	_parser.parse(xmlFileList.c_str());

	std::map<std::string, std::vector<std::string> > fileList = _parser.getFileList();

	std::stringstream ss;
	std::string currentStream;

	bool isClassListEmpty = _classList.empty();

	for(std::map<std::string, std::vector<std::string> >::iterator mapIt = fileList.begin(); mapIt != fileList.end(); ++mapIt) {
		
		if(isClassListEmpty || std::find(_classList.begin(), _classList.end(), mapIt->first)!=_classList.end()) {

			if(_seperateFile) {
				if(_mode == ICON) {
					currentStream = mapIt->first;
				} else {
					currentStream = xmlFileList;
				}
			} else {
				currentStream = SINGLE_FILE;
			}

			for(std::vector<std::string>::iterator fileIt = mapIt->second.begin(); fileIt != mapIt->second.end(); ++fileIt) {

				cv::Mat imageRaw = cv::imread(*fileIt);
				cv::Mat imageBin;
				cv::cvtColor(imageRaw, imageBin, CV_RGB2GRAY);
				imageBin = imageBin > 200;

				for(std::vector<Feature*>::iterator it = _featureList.begin(); it!=_featureList.end(); ++it)  {

					std::vector<double> res = (*it)->execute(imageRaw, imageBin);

					for(std::vector<double>::iterator itValues = res.begin(); itValues!=res.end(); ++itValues) {
						_outputStream[currentStream] << *itValues << ",";
					}
				}

				_outputStream[currentStream] << mapIt->first << "\n";
			}
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
			Logger() << "Creating ARFF file: " << ss.str();
			_outputStream[xmlFile] = std::ofstream(ss.str(), std::ios_base::out | std::ios_base::trunc);
			setARFFHeaders(_outputStream[xmlFile]);
		} else if(!_hasStarted){
			std::stringstream ss;
			if(_classList.empty()) {
				for(std::map<std::string, Icon*>::iterator it = _iconList.begin(); it != _iconList.end(); ++it) {
					ss.str("");
					ss << _outputFolder << "features-" << it->first << ".arff";
					Logger() << "Creating ARFF file: " << ss.str();
					_outputStream[it->first] = std::ofstream(ss.str(), std::ios_base::out | std::ios_base::trunc);
					setARFFHeaders(_outputStream[it->first]);
				}
			} else {
				for(std::vector<std::string>::iterator it = _classList.begin(); it!=_classList.end(); ++it) {
					ss.str("");
					ss << _outputFolder << "features-" << *it << ".arff";
					Logger() << "Creating ARFF file: " << ss.str();
					_outputStream[*it] = std::ofstream(ss.str(), std::ios_base::out | std::ios_base::trunc);
					setARFFHeaders(_outputStream[*it]);
				}
			}
			_hasStarted = true;
		}
	} else if(!_hasStarted){
		std::stringstream ss;
		ss << _outputFolder << "features" << ".arff";
		Logger() << "Creating ARFF file: " << ss.str();
		_outputStream[SINGLE_FILE] = std::ofstream(ss.str(), std::ios_base::out | std::ios_base::trunc);
		setARFFHeaders(_outputStream[SINGLE_FILE]);
		_hasStarted = true;
	}
}


void FeatureExtractor::setARFFHeaders(std::ofstream& stream) {
	stream << "@relation " << _relationName << "\n\n";
	int nbZone;

	for(std::vector<Feature*>::iterator it = _featureList.begin(); it!=_featureList.end(); ++it) {
		std::vector<std::string> names = (*it)->featureNames();

		nbZone = (*it)->getNbZone();
		if(nbZone==1) {
			for(std::vector<std::string>::iterator itName = names.begin(); itName!=names.end(); ++itName) {
					stream << "@attribute " << *itName << " NUMERIC\n";
			}
		} else {
			for(int i=0;i<(*it)->getNbZone();++i) {
				for(std::vector<std::string>::iterator itName = names.begin(); itName!=names.end(); ++itName) {
					stream << "@attribute " << *itName << "_" << i << " NUMERIC\n";
				}
			}
		}
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