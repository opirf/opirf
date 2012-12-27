#include "Feature.h"
#include "Logger.h"

std::vector<double> Feature::execute(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox)
{
	if(_zones.empty())
	{
		return this->featureApply(imageRaw, imageNorm, imageNormBin, boundingBox);
	}

	std::vector<double> ret;
	ret.reserve(_zones.size() * this->featureNames().size());

	for(std::vector<cv::Rect>::const_iterator it = _zones.begin(); it != _zones.end() ; ++it)
	{
		cv::Mat croppedNorm = imageNorm(*it);
		cv::Mat croppedBin = imageNormBin(*it);
		std::vector<double> result = this->featureApply(imageRaw, croppedNorm, croppedBin, boundingBox); 
		ret.insert(ret.end(), result.begin(), result.end());
	}
		
	return ret;	
}