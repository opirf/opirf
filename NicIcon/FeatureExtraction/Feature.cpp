#include "Feature.h"
#include "Logger.h"

std::vector<double> Feature::execute(const cv::Mat& imageRaw, const cv::Mat& imageBin)
{
	if(_zones.empty())
	{
		return this->featureApply(imageRaw, imageBin);
	}

	std::vector<double> ret;
	ret.reserve(_zones.size() * this->featureNames().size());

	for(std::vector<cv::Rect>::const_iterator it = _zones.begin(); it != _zones.end() ; ++it)
	{
		cv::Mat croppedRaw = imageRaw(*it);
		cv::Mat croppedBin = imageBin(*it);
		std::vector<double> result = this->featureApply(croppedRaw, croppedBin); 
		ret.insert(ret.end(), result.begin(), result.end());
	}
		
	return ret;	
}