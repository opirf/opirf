//////////////////////////////////////////////////////////////////////////
// Module IRF, 5-iNFO
// Projet
//////////////////////////////////////////////////////////////////////////
#include "FormAnalyser.h"
#include "BaseFormParser.h"
#include "IconListParser.h"
#include <iostream>
#include <time.h>
#include "Logger.h"

int main (int argc, char** argv) {

	std::stringstream ss;
	FormAnalyser* analyser;
	IconListParser* parser;
	BaseFormParser* formParser;

	parser = new IconListParser();
	parser->parse();

	formParser = new BaseFormParser();
	formParser->parse();

	analyser = new FormAnalyser(parser->getIconList(), formParser->getBaseForm());
	
	clock_t beginTime = clock();
 
	for(int i=0;i<1;++i) {
		try{
			ss.str("");
			ss << "images/database/w000-scans/0000";
			ss << i << ".png";

			analyser->analyse(ss.str());
		} catch(std::exception &e) {
			std::cout<<e.what();
		}

	}

	clock_t endTime = clock();
	Logger() << "Total Time: " << (endTime - beginTime);

	delete parser;
	delete formParser;
	delete analyser;

	system("pause");
}
