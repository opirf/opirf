#include "HoughLinesFeature.h"

HoughLinesFeature::HoughLinesFeature(const std::vector<cv::Rect>& zones) : Feature(zones)
{
}

std::vector<double> HoughLinesFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox) {
	std::vector<cv::Vec2f> lines;
    cv::HoughLines(imageNormBin, lines, 1, CV_PI/180, 350);

	std::vector<double> res;
	res.push_back(lines.size());
	return res;
}
