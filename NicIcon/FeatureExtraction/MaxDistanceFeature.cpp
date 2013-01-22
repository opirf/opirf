#include "MaxDistanceFeature.h"

std::vector<double> MaxDistanceFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox) {
	std::vector<double> ret;

	int maxDistance, currentDistance, firstIndex, j;

	unsigned char *input = (unsigned char*)(imageNormBin.data);

	bool firstPart;
	bool currentFirst;


	// HORIZONTAL
	maxDistance = 0;
	for(int i=0; i<imageNormBin.rows; ++i) {
		j=0;
		while(j<imageNormBin.cols) {
			currentDistance = 0;
			while(input[imageNormBin.step*i+j]==0 && j<imageNormBin.cols) {
				++currentDistance;
				++j;
			}
			++j;
			if(currentDistance>maxDistance && currentDistance!=imageNormBin.cols) {
				maxDistance = currentDistance;
			}
		}
	}

	ret.push_back(maxDistance);

	// VERTICAL
	maxDistance = 0;
	for(int i=0; i<imageNormBin.cols; ++i) {
		j=0;
		while(j<imageNormBin.rows) {
			currentDistance = 0;
			while(input[imageNormBin.step*j+i]==0 && j<imageNormBin.cols) {
				++currentDistance;
				++j;
			}
			++j;
			if(currentDistance>maxDistance && currentDistance!=imageNormBin.rows) {
				maxDistance = currentDistance;
			}
		}
	}

	ret.push_back(maxDistance);

	return ret;
}