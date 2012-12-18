#include "PixelCountFeature.h"

double featureApply(const cv::Mat& image)
{
	return static_cast<double>(image.rows*image.cols - cv::countNonZero(image));
}