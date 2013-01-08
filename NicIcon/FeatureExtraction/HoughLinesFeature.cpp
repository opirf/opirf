#include "HoughLinesFeature.h"
#include <math.h>

using namespace std;
using namespace cv;

HoughLinesFeature::HoughLinesFeature(const std::vector<cv::Rect>& zones) : Feature(zones)
{
}

std::vector<double> HoughLinesFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox) {
	vector<Vec2f> lines;
    HoughLines(imageNormBin, lines, 1, CV_PI/180, 100);
	
	std::vector<double> res;
	res.push_back(lines.size());
	return res;
}
