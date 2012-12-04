#pragma once

#include <vector>
#include <fstream>

#include "Feature.h"

class FeatureExtractor
{
	public:
		FeatureExtractor(const std::string& tnFolder, const std::string& outputFile);
		~FeatureExtractor();
		void addFeature(const Feature* feature);
		void start();

	private:
		std::vector<const Feature*> _featureList;
		std::string _tnFolder;
		std::ofstream _outputStream;

};