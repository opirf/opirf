#include "FeatureExtractor.h"

#include <sstream>
#include <iomanip>
#include <regex>

#include <opencv2\opencv.hpp>

#include "Logger.h"

using namespace std;

FeatureExtractor::FeatureExtractor(const string& tnFolder, const string& outputFolder, const string& relationName, const std::map<std::string, Icon*>& iconList)
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

	for(std::map<std::string, std::vector<std::string> >::iterator mapIt = fileList.begin(); mapIt != fileList.end(); ++mapIt) {

		if(_mode == ICON) {
			currentStream = mapIt->first;
		} else {
			currentStream = xmlFileList;
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

void FeatureExtractor::initFileStream(const std::string& xmlFile) {
	if(_seperateFile) {
		if(_mode == INPUT_FILE) {
			std::smatch m;
			std::regex e (".*/(.*?)\\..*?");
			std::regex_match (xmlFile, m, e);

			std::stringstream ss;
			ss << _outputFolder << *(++m.begin()) << ".arff";
			Logger() << "Creating ARFF file: " << ss.str();
			_outputStream[xmlFile] = std::ofstream(ss.str(), ios_base::out | ios_base::trunc);
			setARFFHeaders(_outputStream[xmlFile]);
		} else if(!_hasStarted){
			std::stringstream ss;
			for(std::map<std::string, Icon*>::iterator it = _iconList.begin(); it != _iconList.end(); ++it) {
				ss.str("");
				ss << _outputFolder << "features-" << it->first << ".arff";
				Logger() << "Creating ARFF file: " << ss.str();
				_outputStream[it->first] = std::ofstream(ss.str(), ios_base::out | ios_base::trunc);
				setARFFHeaders(_outputStream[it->first]);
			}
			_hasStarted = true;
		}
	} else if(!_hasStarted){
		std::stringstream ss;
		ss << _outputFolder << "features" << ".arff";
		Logger() << "Creating ARFF file: " << ss.str();
		_outputStream["single"] = std::ofstream(ss.str(), ios_base::out | ios_base::trunc);
		setARFFHeaders(_outputStream["single"]);
	}
}


void FeatureExtractor::setARFFHeaders(std::ofstream& stream) {
	stream << "@relation " << _relationName << "\n\n";
	int nbZone;

	for(std::vector<Feature*>::iterator it = _featureList.begin(); it!=_featureList.end(); ++it) {
		std::vector<string> names = (*it)->featureNames();

		nbZone = (*it)->getNbZone();
		if(nbZone==1) {
			for(std::vector<string>::iterator itName = names.begin(); itName!=names.end(); ++itName) {
					stream << "@attribute " << *itName << " NUMERIC\n";
			}
		} else {
			for(int i=0;i<(*it)->getNbZone();++i) {
				for(std::vector<string>::iterator itName = names.begin(); itName!=names.end(); ++itName) {
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