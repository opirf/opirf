#pragma once

#include "IconListHandler.h"

#include <xercesc/sax2/SAX2XMLReader.hpp>

class IconListParser
{
	private:
		xercesc::SAX2XMLReader* m_parser;
		IconListHandler* m_handler;

	public:
		IconListParser();
		~IconListParser();
		void parse();

		const std::map<std::string, Icon*>& getIconList() {return m_handler->getIconList();}
};