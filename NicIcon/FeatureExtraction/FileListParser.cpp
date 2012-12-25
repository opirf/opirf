#include "FileListParser.h"
#include "Logger.h"

#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/PlatformUtils.hpp>

FileListParser::FileListParser() {
	try {
		xercesc::XMLPlatformUtils::Initialize();

		_parser = xercesc::XMLReaderFactory::createXMLReader();
		_handler = new FileListHandler();

		_parser->setContentHandler(_handler);
	} catch (const xercesc::XMLException& toCatch) {
		Logger() << toCatch.getMessage();
	}
}

FileListParser::~FileListParser() {
    delete _parser;
    delete _handler;

	xercesc::XMLPlatformUtils::Terminate();
}

void FileListParser::parse(const char* file) {
	try {
		_parser->parse(file);
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