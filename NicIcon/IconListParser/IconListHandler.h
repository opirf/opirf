#pragma once

#include "Icon.h"
#include <map>

#include <xercesc\sax2\DefaultHandler.hpp>

class IconListHandler : public xercesc::DefaultHandler {
	private:
		std::map<std::string, Icon*> m_iconList;
		std::map<std::string, std::string> m_iconSizeList;
		std::string m_crossTemplate;

	public:
		void startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const xercesc::Attributes& attrs);

		const std::string& getCrossTemplate() const {return m_crossTemplate;}
		const std::map<std::string, Icon*>& getIconList() const {return m_iconList;}
		const std::map<std::string, std::string>& getIconSizeList() const {return m_iconSizeList;}
};