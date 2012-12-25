#pragma once

#include "FileListHandler.h"

#include <xercesc/sax2/SAX2XMLReader.hpp>

class FileListParser
{
	private:
		xercesc::SAX2XMLReader* _parser;
		FileListHandler* _handler;

	public:
		FileListParser();
		~FileListParser();
		void parse(const char* file);

		const std::map<std::string, std::vector<std::string> >& getFileList() {return _handler->getFileList();}
};