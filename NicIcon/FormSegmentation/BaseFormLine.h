#pragma once

#include <opencv2\opencv.hpp>
#include <vector>

class BaseFormLine
{
	private:
		cv::Point m_icon;
		std::vector<cv::Point> m_boxList;

	public:
		void setIconPosition(const cv::Point& position) {m_icon = position;}
		void addBox(const cv::Point& position) {m_boxList.push_back(position);}

		const cv::Point& getIconPosition() const {return m_icon;}
		int getBoxNumber() const {return m_boxList.size();}
		const cv::Point& getBoxPosition(int i) const {return m_boxList[i];}
};