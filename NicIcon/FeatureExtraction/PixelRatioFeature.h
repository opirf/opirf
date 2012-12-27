#pragma once

#include <vector>
#include <string>

#include "Feature.h"


class PixelRatioFeature : public Feature
{
	public:
		PixelRatioFeature(const std::vector<cv::Rect>& zones) : Feature(zones) {}

		virtual std::vector<std::string> featureNames() const
		{ 
			std::vector<std::string> ret(1, "PixelRatio");
			return ret; 
		}

	protected:
		virtual std::vector<double> featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox);
		virtual size_t nbResult() { return 1; }
};