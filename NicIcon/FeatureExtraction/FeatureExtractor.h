#pragma once

#include <vector>
#include <map>
#include <fstream>

#include "FileListParser.h"
#include "Feature.h"
#include "Icon.h"
#include "FeatureMode.h"

class FeatureExtractor
{
	public:
		FeatureExtractor(const std::string& tnFolder, const std::string& outputFolder, const std::string& relationName, const std::map<std::string, Icon*>& iconList);
		~FeatureExtractor();
		void addFeature(Feature* feature);
		void extract(const std::string& xmlFileList);
		void separateFile(bool val) {_seperateFile = val;}
		void groupBy(FeatureMode mode) {_mode = mode;}
		void selectWorkingClass(const std::vector<std::string>& classList) {_classList = classList;}

	private:
		void initFileStream(const std::string& xmlFile);
		void setARFFHeaders(std::ofstream& stream);

		std::vector<Feature*> _featureList;
		std::string _tnFolder, _outputFolder, _relationName;
		std::map<std::string, std::ofstream> _outputStream;
		std::map<std::string, Icon*> _iconList;
		FileListParser _parser;
		bool _seperateFile, _hasStarted;
		FeatureMode _mode;
		std::vector<std::string> _classList;

};