#pragma once

#include <vector>
#include <string>

#include <opencv2\opencv.hpp>

class Feature
{
	public:
		Feature(const std::vector<cv::Rect>& zones = std::vector<cv::Rect>()) : _zones(zones) {}

		std::vector<double> execute(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox);

		virtual std::vector<std::string> featureNames() const = 0;
		int getNbZone() const {return _zones.empty()?1:_zones.size();}

	protected:
		virtual std::vector<double> featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox) = 0;

		std::vector<cv::Rect> _zones;
};