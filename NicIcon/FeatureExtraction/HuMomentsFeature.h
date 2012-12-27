#pragma once

#include <vector>
#include <string>

#include "Feature.h"


class HuMomentsFeature : public Feature
{
	public:
		HuMomentsFeature(const std::vector<cv::Rect>& zones) : Feature(zones) {}

		virtual std::vector<std::string> featureNames() const
		{ 
			std::vector<std::string> ret;
			ret.push_back("HuMoment-1");
			ret.push_back("HuMoment-2");
			ret.push_back("HuMoment-3");
			ret.push_back("HuMoment-4");
			ret.push_back("HuMoment-5");
			ret.push_back("HuMoment-6");
			ret.push_back("HuMoment-7");
			return ret; 
		}

	protected:
		virtual std::vector<double> featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox);
		virtual size_t nbResult() { return 7; }
};