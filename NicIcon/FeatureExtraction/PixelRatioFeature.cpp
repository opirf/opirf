#include "PixelRatioFeature.h"
#include "Logger.h"

std::vector<double> PixelRatioFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageBin)
{
	int size = imageBin.rows*imageBin.cols;
	std::vector<double> ret(1, static_cast<double>(size - cv::countNonZero(imageBin))/size);
	return ret;
}