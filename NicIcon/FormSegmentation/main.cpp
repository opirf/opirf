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

	// ------------------------- TRAINING SET -------------------------

	/*#pragma omp parallel for
	for(int j=17;j<35;++j) {
		ss1.str("");
		ss1 << "C:/Temp/opirf/w" << setw(3) << setfill('0') << j << ".xml";
		FormAnalyser* analyser = new FormAnalyser("C:/Temp/opirf/res/", ss1.str(), parser->getIconList(), parser->getIconSizeList(), parser->getCrossTemplate(), formParser->getBaseForm());

		for(int i=0;i<22;++i) {

			try{
				ss.str("");
				ss << root << 'w' << setw(3) << setfill('0') << j << "-scans/" << setw(3) << setfill('0') << j << std::setw(2) << std::setfill('0') << i << ".png";
				analyser->analyse(ss.str());
			} catch(std::exception &e) {
				Logger(omp_get_thread_num(), true) << e.what();
			}
		}
		delete analyser;
	}*/


	// ------------------------- TEST SET -------------------------

	for(int j=1;j<7;++j) {
		ss1.str("");
		ss1 << "C:/Temp/opirf/test-w" << setw(3) << setfill('0') << j << ".xml";
		FormAnalyser* analyser = new FormAnalyser("C:/Temp/opirf/test/", ss1.str(), parser->getIconList(), parser->getIconSizeList(), parser->getCrossTemplate(), formParser->getBaseForm());

		for(int i=1;i<3;++i) {

			try{
				ss.str("");
				ss << root << "tofigureout/s" << setw(2) << setfill('0') << j << "_" << std::setw(4) << std::setfill('0') << i << ".png";
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
