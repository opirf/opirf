#include "HuMomentsFeature.h"
#include "Logger.h"

std::vector<double> HuMomentsFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox)
{
	std::vector<double> ret;
	double hu[7];
	cv::HuMoments(cv::moments(imageNormBin), hu);
	
	for(int i=0;i<7;++i) {
		ret.push_back(hu[i]);
	}
	return ret;
}