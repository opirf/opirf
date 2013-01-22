#include "ConvexHullFeature.h"

std::vector<double> ConvexHullFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox) {

	std::vector<double> ret;

	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;

	/// Find contours
	cv::findContours(imageNormBin, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	std::vector<std::vector<cv::Point> >hull(contours.size());
	for( int i = 0; i < contours.size(); i++ ) {
		convexHull(cv::Mat(contours[i]), hull[i], false);
	}

	cv::RNG rng(12345);
	cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

	int area = 0;
	int length = 0;
	int currentArea, currentArcLength;
	for( int i = 0; i< contours.size(); i++) {
		currentArea = contourArea(hull[i], false);
		if(currentArea > area) {
			area = currentArea;
		}
		currentArcLength = arcLength(hull[i], true);
		if(currentArcLength > length) {
			length = currentArcLength;
		}
	}

    //std::cout << fabs(cv::contourArea(cv::Mat(contour)));

	ret.push_back(area);
	ret.push_back(length);

	return ret;
}

double ConvexHullFeature::distance(cv::Point p1, cv::Point p2) const
{
	return sqrt(static_cast<double>((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y)));
}