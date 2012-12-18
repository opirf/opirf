#pragma once

#include <vector>
#include <string>

#include "Feature.h"


class PixelCountFeature : public Feature
{
	public:
		PixelCountFeature(const std::vector<cv::Rect>& zones) : Feature(zones) {}

		virtual std::vector<std::string> featureNames() 
		{ 
			std::vector<std::string> ret(1, "PixelCount");
			return ; 
		}

	protected:
		virtual std::vector<double> featureApply(const cv::Mat& image);
		virtual size_t nbResult() { return 1; }
};