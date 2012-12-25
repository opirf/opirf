#include "FeatureExtractor.h"

#include <sstream>
#include <iomanip>

#include <opencv2\opencv.hpp>

using namespace std;

FeatureExtractor::FeatureExtractor(const string& tnFolder, const string& outputFile, const string& relationName)
 : _tnFolder(tnFolder), _outputStream(outputFile, ios_base::out | ios_base::trunc), _relationName(relationName)
{

}

FeatureExtractor::~FeatureExtractor()
{
	_outputStream.flush();
	_outputStream.close();
}

void FeatureExtractor::addFeature(Feature* feature) 
{

}

void FeatureExtractor::start()
{
	std::stringstream ss;

	setARFFHeaders();

	for(int j=0;j<1;++j) {

		for(int i=0;i<5;++i) {

			ss.str("");
			// path to be changed absolutely
			ss << _tnFolder << 'w' << setw(3) << setfill('0') << j << "-scans/" << setw(3) << setfill('0') << j << std::setw(2) << std::setfill('0') << i << ".png";
			cv::Mat image = cv::imread(ss.str());

			for(std::vector<Feature*>::iterator it = _featureList.begin(); it!=_featureList.end(); ++it)  {

				std::vector<double> res = (*it)->execute(image);

				for(int i=0; i< (*it)->getNbZone() ; ++i) {

					for(std::vector<double>::iterator itValues = res.begin(); itValues!=res.end(); itValues++) {
						_outputStream << *itValues;

						if(itValues!=--(res.end())) {
							_outputStream << ",";
						}
					}
				}
				_outputStream << "\n";
			}
		}
	}

}

void FeatureExtractor::setARFFHeaders() {
	_outputStream << "@relation " << _relationName << "\n\n";

	for(std::vector<Feature*>::iterator it = _featureList.begin(); it!=_featureList.end(); ++it) {
		std::vector<string> names = (*it)->featureNames();

		for(int i=0;i<(*it)->getNbZone();++i) {
			for(std::vector<string>::iterator itName = names.begin(); itName!=names.end(); itName++) {
				_outputStream << "@attribute " << *itName << "_" << i << "\n";
			}
		}
	}
	
	_outputStream << "@data " << _relationName << "\n";
}