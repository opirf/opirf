#pragma once

#include "BaseForm.h"
#include <map>

#include <xercesc\sax2\DefaultHandler.hpp>

class BaseFormHandler : public xercesc::DefaultHandler {
	private:
		BaseForm m_baseForm;
		BaseFormLine* m_currentLine;

	public:
		void startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const xercesc::Attributes& attrs);
		void endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname);

		const BaseForm& getBaseForm() {return m_baseForm;}

	private:
		int toInt(const std::string& text);
};