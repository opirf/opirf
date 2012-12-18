#include "Feature.h"

std::vector<double> Feature::operator()(const cv::Mat& img)
{
	if(_zones.empty())
	{
		return this->featureApply(img);
	}

	std::vector<double> ret;
	ret.reserve(_zones.size() * this->featureNames().size());

	for(std::vector<cv::Rect>::const_iterator it = _zones.begin(); it != _zones.end() ; ++it)
	{
		cv::Mat cropped = img(*it);
		std::vector<double> result = this->featureApply(cropped); 
		ret.insert(ret.end(), result.begin(), result.end());
	}
		
	return ret;	
}