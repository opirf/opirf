#pragma once

#include <string>
#include "Icon.h"

class IconMatchingException
{
	private:
		double m_confidence1;
		double m_confidence2;

	public:
		IconMatchingException(double confidence1, double confidence2) : m_confidence1(confidence1), m_confidence2(confidence2) {}
		double getConfidence1() const {return m_confidence1;}
		double getConfidence2() const {return m_confidence2;}
};