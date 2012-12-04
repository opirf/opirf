#pragma once

#include "BaseFormHandler.h"

#include <xercesc/sax2/SAX2XMLReader.hpp>

class BaseFormParser
{
	private:
		xercesc::SAX2XMLReader* m_parser;
		BaseFormHandler* m_handler;

	public:
		BaseFormParser();
		~BaseFormParser();
		void parse();

		const BaseForm& getBaseForm() {return m_handler->getBaseForm();}
};