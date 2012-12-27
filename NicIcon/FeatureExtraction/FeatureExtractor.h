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
		FeatureExtractor(const std::string& outputFolder, const std::string& relationName, const std::map<std::string, Icon*>& iconList, int normalizedWidth, int normalizedHeight);
		~FeatureExtractor();
		void addFeature(Feature* feature);
		void extract(const std::string& sourceFolder, const std::string& xmlImageList);
		void separateFile(bool val) {_seperateFile = val;}
		void groupBy(FeatureMode mode) {_mode = mode;}
		void selectWorkingClass(const std::vector<std::string>& classList) {_classList = classList;}

	private:
		void initFileStream(const std::string& xmlFile);
		void setARFFHeaders(std::ofstream& stream);
		cv::Rect normalize(const cv::Mat& src, cv::Mat& dst, int normW, int normH);
		void binariseImage(const cv::Mat& src, cv::Mat& dst);
		void removeNoise(const cv::Mat& src, cv::Mat& dst);
		cv::Rect getBoundingBox(const cv::Mat& src);

		std::vector<Feature*> _featureList;
		std::string _outputFolder, _relationName;
		std::map<std::string, std::ofstream> _outputStream;
		std::map<std::string, Icon*> _iconList;
		FileListParser _parser;
		bool _seperateFile, _hasStarted;
		FeatureMode _mode;
		std::vector<std::string> _classList;
		int _normalizedWidth, _normalizedHeight;

};