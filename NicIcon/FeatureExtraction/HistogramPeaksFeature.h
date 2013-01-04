#pragma once

#include <vector>
#include <string>

#include "Feature.h"
#include "FeatureOrientation.h"


class HistogramPeaksFeature : public Feature
{
	public:
		HistogramPeaksFeature(const std::vector<cv::Rect>& zones, FeatureOrientation orientation, int pixelRange=10, double peakMinGap=0.4, int peakRange=3) : Feature(zones), _orientation(orientation), _pixelRange(pixelRange), _peakMinGap(peakMinGap), _peakRange(peakRange) {}

		virtual std::vector<std::string> featureNames() const
		{ 
			std::vector<std::string> ret;
			std::stringstream ss;
			ss << "Histogram-nbPeaks-";
			if(_orientation == HORIZONTAL) ss << "horizontal";
			else ss << "vertical";
			ret.push_back(ss.str());
			ss.str("");
			ss << "Histogram-maxPeakPos-";
			if(_orientation == HORIZONTAL) ss << "horizontal";
			else ss << "vertical";
			ret.push_back(ss.str());
			return ret; 
		}

	private:
		int _pixelRange, _peakRange;
		double _peakMinGap;
		FeatureOrientation _orientation;

	protected:
		virtual std::vector<double> featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox);
};