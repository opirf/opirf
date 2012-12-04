#include "FeatureExtractor.h"

#include <sstream>
#include <iomanip>

#include <opencv2\opencv.hpp>

using namespace std;

FeatureExtractor::FeatureExtractor(const string& tnFolder, const string& outputFile)
 : _tnFolder(tnFolder), _outputStream(outputFile, ios_base::out | ios_base::trunc)
{

}

FeatureExtractor::~FeatureExtractor()
{
	_outputStream.flush();
	_outputStream.close();
}

void FeatureExtractor::addFeature(const Feature* feature) 
{

}

void FeatureExtractor::start()
{
	std::stringstream ss;

	for(int j=0;j<1;++j) {

		for(int i=0;i<5;++i) {

			ss.str("");
			ss << _tnFolder << 'w' << setw(3) << setfill('0') << j << "-scans/" << setw(3) << setfill('0') << j << std::setw(2) << std::setfill('0') << i << ".png";
			cv::Mat image = cv::imread(ss.str());

			for(std::vector<const Feature*>::iterator it = _featureList.begin(); it!=_featureList.end(); ++it) {
				(**it)(image);
			}
		}
	}

}