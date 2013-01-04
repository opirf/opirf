#include <iomanip>

#include "IconListParser.h"
#include "BaseFormParser.h"

#include "Logger.h"
#include "FeatureExtractor.h"

#include "PixelRatioFeature.h"
#include "CenterOfMassFeature.h"
#include "HuMomentsFeature.h"
#include "HistogramPeaksFeature.h"


int main(int argc, char** argv)
{
	IconListParser parser;
	parser.parse("../resources/settings/icons_list.xml");

	BaseFormParser baseParser;
	baseParser.parse("../resources/settings/base_form.xml");

	clock_t beginTime = clock();

	FeatureExtractor fe("C:/Temp/opirf/", "relation", parser.getIconList(), baseParser.getBaseForm().getBoxWidth(), baseParser.getBaseForm().getBoxHeight());

	std::vector<cv::Rect> zones, empty;
	std::vector<std::string> classList;
	std::stringstream ss;

	zones.push_back(cv::Rect(0, 0, baseParser.getBaseForm().getBoxWidth()/2, baseParser.getBaseForm().getBoxHeight()/2));
	zones.push_back(cv::Rect(baseParser.getBaseForm().getBoxWidth()/2, 0, baseParser.getBaseForm().getBoxWidth()/2, baseParser.getBaseForm().getBoxHeight()/2));
	zones.push_back(cv::Rect(baseParser.getBaseForm().getBoxWidth()/2, baseParser.getBaseForm().getBoxHeight()/2, baseParser.getBaseForm().getBoxWidth()/2, baseParser.getBaseForm().getBoxHeight()/2));
	zones.push_back(cv::Rect(0, baseParser.getBaseForm().getBoxHeight()/2, baseParser.getBaseForm().getBoxWidth()/2, baseParser.getBaseForm().getBoxHeight()/2));

	fe.addFeature(new PixelRatioFeature(empty));
	fe.addFeature(new PixelRatioFeature(zones));
	fe.addFeature(new CenterOfMassFeature(empty));
	fe.addFeature(new CenterOfMassFeature(zones));
	fe.addFeature(new HuMomentsFeature(empty));
	fe.addFeature(new HistogramPeaksFeature(empty, HORIZONTAL, 10, 0.4, 3));
	fe.addFeature(new HistogramPeaksFeature(zones, HORIZONTAL, 10, 0.4, 3));
	fe.addFeature(new HistogramPeaksFeature(empty, VERTICAL, 10, 0.4, 3));
	fe.addFeature(new HistogramPeaksFeature(zones, VERTICAL, 10, 0.4, 3));

	// ------------------------------------------------------

	/*classList.push_back("Accident");
	classList.push_back("Bomb");
	classList.push_back("Fire");
	fe.selectWorkingClass(classList);
	fe.setOutputFileName("Accident-Bomb-Fire");*/
	//fe.separateFile(true);
	//fe.groupBy(ICON);

	#pragma omp parallel for
	for(int i=0;i<4;++i) {
		ss.str("");
		ss << "C:/Temp/opirf/w" << std::setw(3) << std::setfill('0') << i << ".xml";
		fe.extract("C:/Temp/opirf/res/", ss.str());
	}

	fe.save();

	// ------------------------------------------------------

	/*classList.clear();
	classList.push_back("Accident");
	classList.push_back("Car");
	fe.selectWorkingClass(classList);
	fe.setOutputFileName("Accident-Car");
	//fe.separateFile(true);
	//fe.groupBy(ICON);

	for(int i=0;i<4;++i) {
		ss.str("");
		ss << "C:/Temp/opirf/w" << std::setw(3) << std::setfill('0') << i << ".xml";
		fe.extract("C:/Temp/opirf/res/", ss.str());
	}

	fe.save();/*/

	clock_t endTime = clock();
	Logger(-1, true) << "Total Time: " << (endTime - beginTime);

	return 0;
}