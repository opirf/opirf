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

	IconListParser* parser = new IconListParser();
	parser->parse("../resources/settings/icons_list.xml");

	BaseFormParser* formParser = new BaseFormParser();
	formParser->parse("../resources/settings/base_form.xml");

	clock_t beginTime = clock();
	string root = "C:/Temp/opirf/";
	std::stringstream ss, ss1;
	
	#pragma omp parallel for
	for(int j=0;j<4;++j) {
		ss1.str("");
		ss1 << "C:/Temp/opirf/w" << setw(3) << setfill('0') << j << ".xml";
		FormAnalyser* analyser = new FormAnalyser("C:/Temp/opirf/res/", ss1.str(), parser->getIconList(), parser->getIconSizeList(), parser->getCrossTemplate(), formParser->getBaseForm());

		for(int i=0;i<1;++i) {

			try{
				ss.str("");
				ss << root << 'w' << setw(3) << setfill('0') << j << "-scans/" << setw(3) << setfill('0') << j << std::setw(2) << std::setfill('0') << i << ".png";
				analyser->analyse(ss.str());
			} catch(std::exception &e) {
				Logger(omp_get_thread_num(), true) << e.what();
			}
		}
		delete analyser;
	}

	clock_t endTime = clock();
	Logger(-1, true) << "Total Time: " << (endTime - beginTime);

	delete parser;
	delete formParser;

	//system("pause");
}
