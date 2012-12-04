#pragma once

#include <vector>
#include <string>

#include "Feature.h"


class PixelCountFeature : public Feature
{
	public:
		PixelCountFeature(unsigned int nZone) : Feature(nZone) {}

		std::vector<double> operator()(const cv::Mat& image) const;

	private:
		int _nZone;
};