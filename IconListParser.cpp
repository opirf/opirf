#include "IconListParser.h"
#include "Logger.h"

#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/PlatformUtils.hpp>

const char* ICON_LIST_FILE = "settings/icons_list.xml";

IconListParser::IconListParser() {
	try {
		xercesc::XMLPlatformUtils::Initialize();

		m_parser = xercesc::XMLReaderFactory::createXMLReader();
		m_handler = new IconListHandler();

		m_parser->setContentHandler(m_handler);
	} catch (const xercesc::XMLException& toCatch) {
		Logger() << toCatch.getMessage();
	}
}

IconListParser::~IconListParser() {
    delete m_parser;
    delete m_handler;

	xercesc::XMLPlatformUtils::Terminate();
}

void IconListParser::parse() {
	try {
		m_parser->parse(ICON_LIST_FILE);
	}
	catch (const xercesc::XMLException& toCatch) {
		Logger() << toCatch.getMessage();
	}
	catch (const xercesc::SAXParseException& toCatch) {
		Logger() << toCatch.getMessage();
	}
	catch (...) {
		Logger() << "Error while parsing the icon list xml file.";
	}
}