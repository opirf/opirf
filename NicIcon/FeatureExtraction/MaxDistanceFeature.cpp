#include "MaxDistanceFeature.h"

std::vector<double> MaxDistanceFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox) {
	std::vector<double> ret;

	int maxDistance, firstIndex;

	unsigned char *input = (unsigned char*)(imageNormBin.data);

	bool firstPart;
	bool currentFirst;
	
	// HORIZONTAL
	maxDistance = 0;
	for(int i=0; i<imageNormBin.rows; ++i) {

		firstPart = false;
		currentFirst = false;

		for(int j=0; j<imageNormBin.cols; ++j) {
			if(!firstPart && input[imageNormBin.step*j+i]==0) {
				currentFirst = true;
				firstPart = true;
			} else if(firstPart && currentFirst && input[imageNormBin.step*j+i]!=0) {currentFirst=false;firstIndex = j;}
			else if(firstPart && !currentFirst && input[imageNormBin.step*j+i]==0) {
				if(j-firstIndex>maxDistance) {
					maxDistance = j-firstIndex;
				}
			}
		} 
	}

	ret.push_back(maxDistance);

	// VERTICAL
	maxDistance = 0;
	for(int j=0; j<imageNormBin.cols; ++j) {

		firstPart = false;
		currentFirst = false;

		for(int i=0; i<imageNormBin.rows; ++i) {
			if(!firstPart && input[imageNormBin.step*j+i]==0) {
				currentFirst = true;
				firstPart = true;
			} else if(firstPart && currentFirst && input[imageNormBin.step*j+i]!=0) {currentFirst=false;firstIndex = j;}
			else if(firstPart && !currentFirst && input[imageNormBin.step*j+i]==0) {
				if(i-firstIndex>maxDistance) {
					maxDistance = i-firstIndex;
				}
			}
		} 
	}

	ret.push_back(maxDistance);

	return ret;
}