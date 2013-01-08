#pragma once

#include "Feature.h"

class HoughLinesFeature :
	public Feature
{
public:
	HoughLinesFeature(const std::vector<cv::Rect>& zones);
	virtual std::vector<std::string> featureNames() const
		{ 
			std::vector<std::string> ret;
			ret.push_back("HoughLines");
			return ret; 
		}

protected:
	virtual std::vector<double> featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox);

};

