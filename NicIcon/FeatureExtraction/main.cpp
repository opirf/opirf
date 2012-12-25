#include <iomanip>

#include "FeatureExtractor.h"
#include "PixelCountFeature.h"
#include "IconListParser.h"

int main(int argc, char** argv)
{
	IconListParser parser;
	parser.parse("../resources/settings/icons_list.xml");

	FeatureExtractor fe("C:/Temp/opirf/res", "C:/Temp/opirf/", "relation", parser.getIconList());

	fe.addFeature(new PixelCountFeature(std::vector<cv::Rect>()));
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