#include "BoudingBoxFeature.h"

#include <cmath>

std::vector<double> BoudingBoxFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox) {
	std::vector<double> ret;

	double w = boundingBox.width;
	double h = boundingBox.height;

	if(w>h) {
		h = h*imageNorm.cols/w;
		w = imageNorm.cols;
	} else {
		w = w*imageNorm.rows/h;
		h = imageNorm.rows;
	}

	ret.push_back(w/h);
	ret.push_back(w*2 + h*2);
	ret.push_back(w*h);
	ret.push_back(sqrt(w*w+h*h));
	return ret;
}