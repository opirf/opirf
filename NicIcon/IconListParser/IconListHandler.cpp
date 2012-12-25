#include "IconListHandler.h"
#include <iostream>

#include <xercesc\sax2\Attributes.hpp>

void IconListHandler::startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const xercesc::Attributes& attrs) {

	char* tagName = xercesc::XMLString::transcode(localname);

	if(xercesc::XMLString::equals(tagName, "icon")) {
		char* name = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("name")));
		char* description = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("description")));
		char* templatePath = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("template-image")));

		m_iconList[name] = new Icon(name, description, templatePath);

		xercesc::XMLString::release(&name);
		xercesc::XMLString::release(&description);
		xercesc::XMLString::release(&templatePath);
	} else if(xercesc::XMLString::equals(tagName, "size")) {
		char* type = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("type")));
		char* templatePath = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("template-image")));

		m_iconSizeList[type] = templatePath;

		xercesc::XMLString::release(&type);
		xercesc::XMLString::release(&templatePath);
	} else if(xercesc::XMLString::equals(tagName, "cross")) {
		char* templatePath = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("template-image")));

		m_crossTemplate = templatePath;

		xercesc::XMLString::release(&templatePath);
	}

    xercesc::XMLString::release(&tagName);
}