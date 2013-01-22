#pragma once

#include <vector>
#include <string>

#include "Feature.h"
#include "FeatureOrientation.h"


class ConvexHullFeature : public Feature
{
	public:
		ConvexHullFeature(const std::vector<cv::Rect>& zones) : Feature(zones) {}

		virtual std::vector<std::string> featureNames() const
		{ 
			std::vector<std::string> ret;
			ret.push_back("ConvexHullFeature-Area");
			ret.push_back("ConvexHullFeature-Perimeter");
			return ret; 
		}


	private:
		double distance(cv::Point p1, cv::Point p2) const;

	protected:
		virtual std::vector<double> featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox);
};