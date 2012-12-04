#include "BaseFormParser.h"
#include "Logger.h"

#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/PlatformUtils.hpp>

const char* BASE_FORM_FILE = "settings/base_form.xml";

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

void BaseFormParser::parse() {
	try {
		m_parser->parse(BASE_FORM_FILE);
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