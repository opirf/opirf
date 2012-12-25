#include "FileListHandler.h"
#include "Logger.h"
#include <iostream>
#include <stdlib.h>

#include <xercesc\sax2\Attributes.hpp>

void FileListHandler::startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const xercesc::Attributes& attrs) {

	char* tagName = xercesc::XMLString::transcode(localname);

	_isFile = false;

	if(xercesc::XMLString::equals(tagName, "class")) {
		char* iconClass = xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("name")));

		_fileList[iconClass] = std::vector<std::string>();
		_currentClass = iconClass;

		xercesc::XMLString::release(&iconClass);
	} else if(xercesc::XMLString::equals(tagName, "file")) {
		_isFile = true;
	}

    xercesc::XMLString::release(&tagName);
}


void FileListHandler::characters(const XMLCh *const chars, const XMLSize_t length) {
	if(_isFile) {
		char* value = xercesc::XMLString::transcode(chars);
		std::stringstream ss;
		
		for(int i=0; i < length; i++) {
		   if(value[i] != ' ' && value[i] != '\n' && value[i] != '\t') {
			   ss << value[i];
		   }
		}

		std::string final = ss.str();

		if(final.length()>0) {
			_fileList[_currentClass].push_back(final);
		}

		xercesc::XMLString::release(&value);
	}
}