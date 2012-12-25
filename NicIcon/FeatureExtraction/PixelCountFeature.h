#pragma once

#include <vector>
#include <string>

#include "Feature.h"


class PixelCountFeature : public Feature
{
	public:
		PixelCountFeature(const std::vector<cv::Rect>& zones) : Feature(zones) {}

		virtual std::vector<std::string> featureNames() const
		{ 
			std::vector<std::string> ret(1, "PixelCount");
			return ret; 
		}

	protected:
		virtual std::vector<double> featureApply(const cv::Mat& imageRaw, const cv::Mat& imageGray);
		virtual size_t nbResult() { return 1; }
};