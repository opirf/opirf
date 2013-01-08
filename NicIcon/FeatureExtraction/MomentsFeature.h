#pragma once

#include <vector>
#include <string>

#include "Feature.h"


class MomentsFeature : public Feature
{
	public:
		MomentsFeature(const std::vector<cv::Rect>& zones) : Feature(zones) {}

		virtual std::vector<std::string> featureNames() const
		{ 
			std::vector<std::string> ret;

			ret.push_back("SpatialMoment-m00");
			ret.push_back("SpatialMoment-m10");
			ret.push_back("SpatialMoment-m01");
			ret.push_back("SpatialMoment-m20");
			ret.push_back("SpatialMoment-m11");
			ret.push_back("SpatialMoment-m02");
			ret.push_back("SpatialMoment-m30");
			ret.push_back("SpatialMoment-m21");
			ret.push_back("SpatialMoment-m12");
			ret.push_back("SpatialMoment-m03");
			
			ret.push_back("CentralMoment-mu20");
			ret.push_back("CentralMoment-mu11");
			ret.push_back("CentralMoment-mu02");
			ret.push_back("CentralMoment-mu30");
			ret.push_back("CentralMoment-mu21");
			ret.push_back("CentralMoment-mu12");
			ret.push_back("CentralMoment-mu03");
    
			ret.push_back("CentralNormalizedMoment-nu20");
			ret.push_back("CentralNormalizedMoment-nu11");
			ret.push_back("CentralNormalizedMoment-nu02");
			ret.push_back("CentralNormalizedMoment-nu30");
			ret.push_back("CentralNormalizedMoment-nu21");
			ret.push_back("CentralNormalizedMoment-nu12");
			ret.push_back("CentralNormalizedMoment-nu03");
			return ret; 
		}

	protected:
		virtual std::vector<double> featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox);
};