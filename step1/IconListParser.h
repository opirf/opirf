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

		const std::string& getCrossTemplate() const {return m_handler->getCrossTemplate();}
		const std::map<std::string, Icon*>& getIconList() const {return m_handler->getIconList();}
		const std::map<std::string, std::string>& getIconSizeList() const {return m_handler->getIconSizeList();}
};