#include "ConnectedComponentFeature.h"

#include <opencv2\opencv.hpp>

std::vector<double> ConnectedComponentFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox) {
	
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imageNormBin, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_TC89_KCOS);

	std::vector<double> ret;
	ret.push_back(static_cast<double>(contours.size()));

	return ret;
}
