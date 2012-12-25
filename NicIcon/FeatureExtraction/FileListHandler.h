#pragma once

#include <map>
#include <vector>

#include <xercesc\sax2\DefaultHandler.hpp>

class FileListHandler : public xercesc::DefaultHandler {
	private:
		std::map<std::string, std::vector<std::string> > _fileList;
		std::string _currentClass;
		bool _isFile;

	public:
		void startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const xercesc::Attributes& attrs);
		void characters(const XMLCh *const chars, const XMLSize_t length);

		const std::map<std::string, std::vector<std::string> >& getFileList() {return _fileList;}
};