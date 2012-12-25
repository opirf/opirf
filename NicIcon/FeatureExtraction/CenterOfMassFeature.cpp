#include "CenterOfMassFeature.h"
#include "Logger.h"

std::vector<double> CenterOfMassFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageBin)
{
	std::vector<double> ret;

	int x = 0;
	int y = 0;
	//int nbPixel =  cv::countNonZero(imageBin);
	int nbPixel = 0;

	unsigned char *input = (unsigned char*)(imageBin.data);
	
	for(int i=0; i<imageBin.rows; ++i) {
		for(int j=0; j<imageBin.cols; ++j) {
			if(input[imageBin.step*j+i]==0) {
				++nbPixel;
				x += j;
				y += i;
			}
		}
	}

	if(nbPixel==0) {
		ret.push_back(0);
		ret.push_back(0);
	} else {
		ret.push_back(x/nbPixel);
		ret.push_back(y/nbPixel);
	}

	return ret;
}