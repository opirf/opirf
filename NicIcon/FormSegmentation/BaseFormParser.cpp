#include "BaseFormParser.h"
#include "Logger.h"

#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/PlatformUtils.hpp>

BaseFormParser::BaseFormParser() {
	try {
		xercesc::XMLPlatformUtils::Initialize();

		m_parser = xercesc::XMLReaderFactory::createXMLReader();
		m_handler = new BaseFormHandler();

		m_parser->setContentHandler(m_handler);
	} catch (const xercesc::XMLException& toCatch) {
		Logger() << toCatch.getMessage();
	}
}

BaseFormParser::~BaseFormParser() {
    delete m_parser;
    delete m_handler;

	xercesc::XMLPlatformUtils::Terminate();
}

void BaseFormParser::parse(const char* file) {
	try {
		m_parser->parse(file);
	}
	catch (const xercesc::XMLException& toCatch) {
		Logger() << toCatch.getMessage();
	}
	catch (const xercesc::SAXParseException& toCatch) {
		Logger() << toCatch.getMessage();
	}
	catch (...) {
		Logger() << "Error while parsing the base form xml file.";
	}
}