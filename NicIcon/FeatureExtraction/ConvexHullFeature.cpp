#include "ConvexHullFeature.h"

std::vector<double> ConvexHullFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox) {

	std::vector<double> ret;

	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;

	//cv::cvtColor(imageNorm, imageNormBin, CV_RGB2GRAY);
	//cv::blur(imageNormBin, imageNormBin, cv::Size(3,3));
	//cv::threshold(imageNormBin, imageNormBin, 254, 255, cv::THRESH_BINARY);

	/// Find contours
	cv::findContours(imageNormBin, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS , cv::Point(0, 0));
	
	/// Find the convex hull object for each contour
	int max,index;
	std::vector<std::vector<cv::Point> > hull(1);
	max = 0;
	for(int i=0; i<contours.size(); ++i) {
		if(contours[i].size()>max) {
			max = contours[i].size();
			index = i;
		}
		//cv::convexHull(cv::Mat(contours[i]), hull[i], false);
	}
	cv::convexHull(cv::Mat(contours[index]), hull[0], false);
	//cv::convexHull(cv::Mat(contours[0]), hull[0], false);

	double perimeter = 0;
	/*for(int i=0; i<contours.size(); ++i) {
		for(int j=0; j<hull[i].size()-1; ++j) {
			perimeter += distance(hull[i][j], hull[i][j+1]);
		}
	}*/

	ret.push_back(perimeter);

	std::cout << perimeter << std::endl;
	
	cv::RNG rng(12345);
	cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

	//cv::Mat drawing = cv::Mat::zeros( imageNormBin.size(), CV_8UC3 );
	/*for( int i = 0; i< contours.size(); i++ ) {
		cv::Mat drawing = cv::Mat::zeros( imageNormBin.size(), CV_8UC3 );
		//drawContours(drawing, contours, i, color, 1, 8, cv::vector<cv::Vec4i>(), 0, cv::Point() );
		drawContours(drawing, hull, i, color, 1, 8, cv::vector<cv::Vec4i>(), 0, cv::Point() );
		cv::imshow("dd", drawing);
		cv::waitKey();
	}*/
	cv::Mat drawing = cv::Mat::zeros( imageNormBin.size(), CV_8UC3 );
	//drawContours(drawing, contours, i, color, 1, 8, cv::vector<cv::Vec4i>(), 0, cv::Point() );
	drawContours(drawing, hull, 0, color, 1, 8, cv::vector<cv::Vec4i>(), 0, cv::Point() );
	cv::imshow("dd", drawing);
	cv::waitKey();

	return ret;
}

double ConvexHullFeature::distance(cv::Point p1, cv::Point p2) const
{
	return sqrt(static_cast<double>((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y)));
}