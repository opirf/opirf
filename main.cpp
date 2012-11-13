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
#include <omp.h>

int main (int argc, char** argv) {

	std::stringstream ss;
	FormAnalyser* analyser;
	IconListParser* parser;
	BaseFormParser* formParser;
	clock_t beginTime;

	parser = new IconListParser();
	parser->parse();

	formParser = new BaseFormParser();
	formParser->parse();

	analyser = new FormAnalyser(parser->getIconList(), parser->getIconSizeList(), parser->getCrossTemplate(), formParser->getBaseForm());
	
	beginTime = clock();
	for(int i=0;i<5;++i) {
		try{
			ss.str("");
			ss << "images/database/w000-scans/0000" << i << ".png";
			analyser->analyse(ss.str());
		} catch(std::exception &e) {
			Logger() << e.what();
		}

	}

	clock_t endTime = clock();
	Logger() << "Total Time: " << (endTime - beginTime);

	delete parser;
	delete formParser;
	delete analyser;

	//system("pause");
}
