#include <iomanip>

#include "FeatureExtractor.h"
#include "PixelRatioFeature.h"
#include "CenterOfMassFeature.h"
#include "IconListParser.h"
#include "BaseFormParser.h"

int main(int argc, char** argv)
{
	IconListParser parser;
	parser.parse("../resources/settings/icons_list.xml");

	BaseFormParser baseParser;
	baseParser.parse("../resources/settings/base_form.xml");

	FeatureExtractor fe("C:/Temp/opirf/res", "C:/Temp/opirf/", "relation", parser.getIconList());

	std::vector<cv::Rect> zones;
	zones.push_back(cv::Rect(0,0,baseParser.getBaseForm().getBoxWidth()/2, baseParser.getBaseForm().getBoxHeight()/2));
	zones.push_back(cv::Rect(baseParser.getBaseForm().getBoxWidth()/2, baseParser.getBaseForm().getBoxHeight()/2, baseParser.getBaseForm().getBoxWidth()/2, baseParser.getBaseForm().getBoxHeight()/2));

	fe.addFeature(new PixelRatioFeature(std::vector<cv::Rect>()));
	fe.addFeature(new PixelRatioFeature(zones));
	fe.addFeature(new CenterOfMassFeature(std::vector<cv::Rect>()));
	fe.addFeature(new CenterOfMassFeature(zones));
	fe.separateFile(true);
	//fe.groupBy(ICON);

	std::stringstream ss;

	for(int i=0;i<4;++i) {
		ss.str("");
		ss << "C:/Temp/opirf/w" << std::setw(3) << std::setfill('0') << i << ".xml";
		fe.extract(ss.str());
	}
	//system("pause");

	return 0;
}