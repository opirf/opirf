#pragma once

#include <vector>
#include <string>

#include "Feature.h"
#include "FeatureOrientation.h"


class MaxDistanceFeature : public Feature
{
	public:
		MaxDistanceFeature(const std::vector<cv::Rect>& zones) : Feature(zones) {}

		virtual std::vector<std::string> featureNames() const
		{ 
			std::vector<std::string> ret;
			ret.push_back("MaxDistance-Horizontal");
			ret.push_back("MaxDistance-Vertical");
			return ret; 
		}


	protected:
		virtual std::vector<double> featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox);
};