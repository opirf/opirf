#pragma once

#include <string>
#include <map>
#include <opencv2\opencv.hpp>

#include "Icon.h"
#include "BaseForm.h"

class FormAnalyser
{
	private:
		cv::Mat m_form, m_workingForm, m_crossTemplate;
		std::map<std::string, cv::Mat> m_iconSizeMatList;
		cv::Point m_crossSubPosition, m_crossSupPosition;
		std::map<std::string, cv::Mat> m_iconMatList;
		std::string currentImage, _outputDirectory;
		BaseForm m_baseForm;

	public:
		FormAnalyser(const std::string& outputDirectory, const std::map<std::string, Icon*>& iconList, const std::map<std::string, std::string>& iconSizeList, const std::string& crossTemplate, const BaseForm& baseForm);
		void analyse(const std::string& formPath);

	private:
		void getSupCross();
		void getSubCross();
		void reposition();
		void adjustAngle();
		void resize();
		void setUpTemplates(const std::map<std::string, Icon*>& iconList, const std::map<std::string, std::string>& iconSizeList, const std::string& crossTemplate);
		void handleLines();
		void saveBoxData(const std::string& iconClass, const std::string& iconSize, cv::Point position, int i, int j);
		const std::string& findIcon(const cv::Point& roi);
		std::string findIconSize(const cv::Point& roi);
		const std::string& pad(const std::string& s, std::string& out, int length);
};