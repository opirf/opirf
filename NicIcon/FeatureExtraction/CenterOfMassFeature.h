#pragma once

#include <vector>
#include <string>

#include "Feature.h"


class CenterOfMassFeature : public Feature
{
	public:
		CenterOfMassFeature(const std::vector<cv::Rect>& zones) : Feature(zones) {}

		virtual std::vector<std::string> featureNames() const
		{ 
			std::vector<std::string> ret;
			ret.push_back("CenterOfMass-x");
			ret.push_back("CenterOfMass-y");
			return ret; 
		}

	protected:
		virtual std::vector<double> featureApply(const cv::Mat& imageRaw, const cv::Mat& imageBin);
		virtual size_t nbResult() { return 2; }
};