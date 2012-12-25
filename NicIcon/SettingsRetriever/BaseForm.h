#pragma once

#include "BaseFormLine.h"

#include <string>
#include <vector>
#include <map>

class BaseForm
{
	private:
		int m_formWidth, m_formHeight, m_iconRoiW, m_iconRoiH, m_boxWidth, m_boxHeight;
		cv::Point m_topCross, m_bottomCross;
		std::vector<BaseFormLine*> m_lineList;

	public:
		void addLine(BaseFormLine* line) {m_lineList.push_back(line);}
		void setFormDimension(int width, int height) {m_formWidth = width; m_formHeight = height;}
		void setIconROIDimension(int width, int height) {m_iconRoiW = width; m_iconRoiH = height;}
		void setBoxDimension(int width, int height) {m_boxWidth = width; m_boxHeight = height;}
		void setTopCrossPosition(const cv::Point& position) {m_topCross = position;}
		void setBottomCrossPosition(const cv::Point& position) {m_bottomCross = position;}

		int getFormWidth() const {return m_formWidth;}
		int getFormHeight() const {return m_formHeight;}
		int getIconROIWidth() const {return m_iconRoiW;}
		int getIconROIHeight() const {return m_iconRoiH;}
		int getBoxWidth() const {return m_boxWidth;}
		int getBoxHeight() const {return m_boxHeight;}

		const cv::Point&  getTopCrossPosition() const {return m_topCross;}
		const cv::Point&  getBottomCrossPosition() const {return m_bottomCross;}

		int getLineNumber() const {return m_lineList.size();}
		BaseFormLine* getLine(int i) const {return m_lineList[i];}
};