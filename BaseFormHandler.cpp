#include "BaseFormHandler.h"
#include "Logger.h"
#include <iostream>
#include <stdlib.h>

#include <xercesc\sax2\Attributes.hpp>

void BaseFormHandler::startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const xercesc::Attributes& attrs) {

	char* tagName = xercesc::XMLString::transcode(localname);

	if(xercesc::XMLString::equals(tagName, "dimension")) {
		char* width = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("width")));
		char* height = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("height")));

		m_baseForm.setFormDimension(toInt(width), toInt(height));

		xercesc::XMLString::release(&width);
		xercesc::XMLString::release(&height);
	} else if(xercesc::XMLString::equals(tagName, "icon-roi")) {
		char* width = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("width")));
		char* height = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("height")));

		m_baseForm.setIconROIDimension(toInt(width), toInt(height));

		xercesc::XMLString::release(&width);
		xercesc::XMLString::release(&height);
	} else if(xercesc::XMLString::equals(tagName, "box-dimension")) {
		char* width = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("width")));
		char* height = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("height")));

		m_baseForm.setBoxDimension(toInt(width), toInt(height));

		xercesc::XMLString::release(&width);
		xercesc::XMLString::release(&height);
	} else if(xercesc::XMLString::equals(tagName, "top-cross")) {
		char* x = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("position-x")));
		char* y = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("position-y")));

		m_baseForm.setTopCrossPosition(cv::Point(toInt(x), toInt(y)));

		xercesc::XMLString::release(&x);
		xercesc::XMLString::release(&y);
	} else if(xercesc::XMLString::equals(tagName, "bottom-cross")) {
		char* x = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("position-x")));
		char* y = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("position-y")));

		m_baseForm.setBottomCrossPosition(cv::Point(toInt(x), toInt(y)));

		xercesc::XMLString::release(&x);
		xercesc::XMLString::release(&y);
	} else if(xercesc::XMLString::equals(tagName, "line")) {
		m_currentLine = new BaseFormLine();
	} else if(xercesc::XMLString::equals(tagName, "icon")) {
		char* x = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("position-x")));
		char* y = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("position-y")));

		m_currentLine->setIconPosition(cv::Point(toInt(x), toInt(y)));

		xercesc::XMLString::release(&x);
		xercesc::XMLString::release(&y);
	} else if(xercesc::XMLString::equals(tagName, "box")) {
		char* x = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("position-x")));
		char* y = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("position-y")));

		m_currentLine->addBox(cv::Point(toInt(x), toInt(y)));

		xercesc::XMLString::release(&x);
		xercesc::XMLString::release(&y);
	}

    xercesc::XMLString::release(&tagName);
}

void BaseFormHandler::endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname) {
	char* tagName = xercesc::XMLString::transcode(localname);

	if(xercesc::XMLString::equals(tagName, "line")) {
		m_baseForm.addLine(m_currentLine);
	}

    xercesc::XMLString::release(&tagName);
}

int BaseFormHandler::toInt(const std::string& text)
{
    std::istringstream iss(text);
    int num;
    iss >> num;
    return num;
}