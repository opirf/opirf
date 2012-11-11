#pragma once

#include <string>
#include "Icon.h"

class IconMatchingException
{
	private:
		double m_confidence;

	public:
		IconMatchingException(double confidence) : m_confidence(confidence) {}
		double getConfidence() const {return m_confidence;}
};