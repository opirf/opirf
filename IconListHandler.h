#pragma once

#include "Icon.h"
#include <map>

#include <xercesc\sax2\DefaultHandler.hpp>

class IconListHandler : public xercesc::DefaultHandler {
	private:
		std::map<std::string, Icon*> m_iconList;

	public:
		void startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const xercesc::Attributes& attrs);

		const std::map<std::string, Icon*>& getIconList() {return m_iconList;}
};