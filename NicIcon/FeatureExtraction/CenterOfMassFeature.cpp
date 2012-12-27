#include "CenterOfMassFeature.h"
#include "Logger.h"

std::vector<double> CenterOfMassFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox)
{
	std::vector<double> ret;

	int x = 0;
	int y = 0;
	//int nbPixel =  cv::countNonZero(imageBin);
	int nbPixel = 0;

	unsigned char *input = (unsigned char*)(imageNormBin.data);
	
	for(int i=0; i<imageNormBin.rows; ++i) {
		for(int j=0; j<imageNormBin.cols; ++j) {
			if(input[imageNormBin.step*j+i]==0) {
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