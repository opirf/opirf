#include "PixelCountFeature.h"
#include "Logger.h"

std::vector<double> PixelCountFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageGray)
{
	cv::Mat imageBin = imageGray > 200;
	std::vector<double> ret(1, static_cast<double>(imageGray.rows*imageGray.cols - cv::countNonZero(imageBin)));
	return ret;
}