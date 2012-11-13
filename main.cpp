//////////////////////////////////////////////////////////////////////////
// Module IRF, 5-iNFO
// Projet
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <sstream>
#include <time.h>
#include <omp.h>

#include "Logger.h"
#include "FormAnalyser.h"
#include "BaseFormParser.h"
#include "IconListParser.h"

using namespace std;

int main (int argc, char** argv) {

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
	string root = "images/database/";
	for(int j=0;j<1;++j) {


		for(int i=0;i<22;++i) {
			try{
				std::stringstream ss;
				ss << root << 'w' << setw(3) << setfill('0') << j << "-scans/" << setw(3) << setfill('0') << j << std::setw(2) << std::setfill('0') << i << ".png";
				analyser->analyse(ss.str());
			} catch(std::exception &e) {
				Logger() << e.what();
			}

		}
	}

	clock_t endTime = clock();
	Logger() << "Total Time: " << (endTime - beginTime);

	delete parser;
	delete formParser;
	delete analyser;

	//system("pause");
}
