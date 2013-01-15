#pragma once
#include "feature.h"
class ConnectedComponentFeature : public Feature
{
public:
	ConnectedComponentFeature(const std::vector<cv::Rect>& zones) : Feature(zones) {}

	virtual std::vector<std::string> featureNames() const
	{ 
		std::vector<std::string> ret(1, "ConnectedComponent");
		return ret; 
	}

protected:
	virtual std::vector<double> featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox);
};

