#pragma once

#include <vector>
#include <fstream>

#include "Feature.h"

class FeatureExtractor
{
	public:
		FeatureExtractor(const std::string& tnFolder, const std::string& outputFile, const std::string& relationName);
		~FeatureExtractor();
		void addFeature(Feature* feature);
		void start();

	private:
		void setARFFHeaders();
		std::vector<Feature*> _featureList;
		std::string _tnFolder, _relationName;
		std::ofstream _outputStream;

};