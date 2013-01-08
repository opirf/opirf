#include "MomentsFeature.h"

std::vector<double> MomentsFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox)
{
	std::vector<double> ret;

	cv::Moments m = cv::moments(imageNormBin);

	ret.push_back(m.m00);
	ret.push_back(m.m10);
	ret.push_back(m.m01);
	ret.push_back(m.m20);
	ret.push_back(m.m11);
	ret.push_back(m.m02);
	ret.push_back(m.m30);
	ret.push_back(m.m21);
	ret.push_back(m.m12);
	ret.push_back(m.m03);
			
	ret.push_back(m.mu20);
	ret.push_back(m.mu11);
	ret.push_back(m.mu02);
	ret.push_back(m.mu30);
	ret.push_back(m.mu21);
	ret.push_back(m.mu12);
	ret.push_back(m.mu03);
    
	ret.push_back(m.nu20);
	ret.push_back(m.nu11);
	ret.push_back(m.nu02);
	ret.push_back(m.nu30);
	ret.push_back(m.nu21);
	ret.push_back(m.nu12);
	ret.push_back(m.nu03);

	return ret;
}