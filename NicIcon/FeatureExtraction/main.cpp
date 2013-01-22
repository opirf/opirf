#include <iomanip>

#include "IconListParser.h"
#include "BaseFormParser.h"

#include "Logger.h"
#include "FeatureExtractor.h"

#include "PixelRatioFeature.h"
#include "CenterOfMassFeature.h"
#include "HuMomentsFeature.h"
#include "HistogramPeaksFeature.h"
#include "MomentsFeature.h"
#include "BoundingBoxFeature.h"
#include "MaxDistanceFeature.h"
#include "ConvexHullFeature.h"
#include "HoughLinesFeature.h"

int main(int argc, char** argv)
{
	IconListParser parser;
	parser.parse("../resources/settings/icons_list.xml");

	BaseFormParser baseParser;
	baseParser.parse("../resources/settings/base_form.xml");

	clock_t beginTime = clock();

	FeatureExtractor fe("C:/Temp/opirf/", "relation", parser.getIconList(), baseParser.getBaseForm().getBoxWidth(), baseParser.getBaseForm().getBoxHeight());

	std::vector<cv::Rect> zonesFour, zonesSixH, zonesSixV, empty;
	std::vector<std::string> classList;
	std::stringstream ss;
	int width = baseParser.getBaseForm().getBoxWidth();
	int height = baseParser.getBaseForm().getBoxHeight();

	zonesSixH.push_back(cv::Rect(0, 0, width/3, height/2));
	zonesSixH.push_back(cv::Rect(0, height/2, width/3, height/2));
	zonesSixH.push_back(cv::Rect(width/3, 0, width/3, height/2));
	zonesSixH.push_back(cv::Rect(width/3, height/2, width/3, height/2));
	zonesSixH.push_back(cv::Rect(2*width/3, 0, width/3, height/2));
	zonesSixH.push_back(cv::Rect(2*width/3, height/2, width/3, height/2));

	zonesSixV.push_back(cv::Rect(0, 0, width/2, height/3));
	zonesSixV.push_back(cv::Rect(width/2, 0, width/2, height/3));
	zonesSixV.push_back(cv::Rect(0, height/3, width/2, height/3));
	zonesSixV.push_back(cv::Rect(width/2, height/3, width/2, height/3));
	zonesSixV.push_back(cv::Rect(0, 2*height/3, width/2, height/3));
	zonesSixV.push_back(cv::Rect(width/2, 2*height/3, width/2, height/3));

	zonesFour.push_back(cv::Rect(0, 0, width/2, height/2));
	zonesFour.push_back(cv::Rect(width/2, 0, width/2, height/2));
	zonesFour.push_back(cv::Rect(width/2, height/2, width/2, height/2));
	zonesFour.push_back(cv::Rect(0, height/2, width/2, height/2));


	fe.addFeature(new PixelRatioFeature(empty));
	fe.addFeature(new PixelRatioFeature(zonesFour));
	//fe.addFeature(new PixelRatioFeature(zonesVerti));
	fe.addFeature(new CenterOfMassFeature(empty));
	fe.addFeature(new CenterOfMassFeature(zonesFour));
	//fe.addFeature(new CenterOfMassFeature(zonesFour));
	//fe.addFeature(new HuMomentsFeature(empty));
	fe.addFeature(new HistogramPeaksFeature(empty, HORIZONTAL, 5, 0.5, 5));
	fe.addFeature(new HistogramPeaksFeature(zonesSixH, HORIZONTAL, 5, 0.5, 5));
	//fe.addFeature(new HistogramPeaksFeature(zonesSixV, HORIZONTAL, 5, 0.5, 5));
	fe.addFeature(new HistogramPeaksFeature(empty, VERTICAL, 5, 0.5, 5));
	fe.addFeature(new HistogramPeaksFeature(zonesSixH, VERTICAL, 5, 0.5, 5));
	//fe.addFeature(new HistogramPeaksFeature(zonesSixV, VERTICAL, 5, 0.5, 5));
	fe.addFeature(new MomentsFeature(empty));
	fe.addFeature(new MomentsFeature(zonesSixH));
	//fe.addFeature(new MomentsFeature(zonesSixV));
	fe.addFeature(new BoundingBoxFeature());
	fe.addFeature(new MaxDistanceFeature(empty));
	fe.addFeature(new MaxDistanceFeature(zonesSixV));
	fe.addFeature(new ConvexHullFeature(empty));
	//fe.addFeature(new HoughLinesFeature(empty));

	// ------------------------------------------------------

	/*classList.push_back("Accident");
	//classList.push_back("Bomb");
	//classList.push_back("Fire");
	fe.selectWorkingClass(classList);
	fe.setOutputFileName("Accident");*/
	//fe.separateFile(true);
	//fe.groupBy(ICON);

	// ------------------------------- TRAINING SET -------------------------------

	/*fe.setOutputFileName("training-set");

	#pragma omp parallel for
	for(int i=0;i<10;++i) {
		ss.str("");
		ss << "C:/Temp/opirf/w" << std::setw(3) << std::setfill('0') << i << ".xml";
		fe.extract("C:/Temp/opirf/res/", ss.str());
	}

	fe.save();*/

	// ------------------------------- TEST SET -------------------------------

	fe.setOutputFileName("test-set");

	#pragma omp parallel for
	for(int i=1;i<7;++i) {
		ss.str("");
		ss << "C:/Temp/opirf/test-w" << std::setw(3) << std::setfill('0') << i << ".xml";
		fe.extract("C:/Temp/opirf/test/", ss.str());
	}

	fe.save();

	// ------------------------------------------------------



	clock_t endTime = clock();
	Logger(-1, true) << "Total Time: " << (endTime - beginTime);

	return 0;
}