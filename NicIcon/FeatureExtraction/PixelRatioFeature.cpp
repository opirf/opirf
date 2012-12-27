#include "PixelRatioFeature.h"
#include "Logger.h"

std::vector<double> PixelRatioFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox)
{
	int size = imageNormBin.rows*imageNormBin.cols;
	std::vector<double> ret(1, static_cast<double>(size - cv::countNonZero(imageNormBin))/size);
	return ret;
}