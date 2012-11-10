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
		cv::Point m_crossSubPosition, m_crossSupPosition;
		std::map<std::string, Icon*> m_iconList;
		std::map<std::string, cv::Mat> m_iconMatList;
		BaseForm m_baseForm;

	public:
		FormAnalyser(const std::map<std::string, Icon*>& iconList, const BaseForm& baseForm);

		void analyse(std::string formPath);

	private:
		void getSupCross();
		void getSubCross();
		void setUpTemplates();
		void handleLines();
		void saveBoxContent(std::string iconClass, cv::Point position, int i, int j);
		const std::string& findIcon(const cv::Point& roi);
};