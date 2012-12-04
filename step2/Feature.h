#pragma once

#include <vector>
#include <string>

#include <opencv2\opencv.hpp>

class Feature
{
	public:
		Feature(unsigned int nZone = 1) : _nZone(nZone) {}

		virtual std::vector<double> operator()(const cv::Mat& image) const = 0;

	private:
		int _nZone;
};