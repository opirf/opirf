#pragma once

#include <vector>
#include <string>

#include "Feature.h"


class BoundingBoxFeature : public Feature
{
	public:
		BoundingBoxFeature() : Feature(std::vector<cv::Rect>()) {}

		virtual std::vector<std::string> featureNames() const
		{ 
			std::vector<std::string> ret;
			ret.push_back("BoudingBox-WidthHeightRatio");
			ret.push_back("BoudingBox-Perimeter");
			ret.push_back("BoudingBox-Area");
			ret.push_back("BoudingBox-Diagonal");
			return ret; 
		}

	protected:
		virtual std::vector<double> featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox);
};