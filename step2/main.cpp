#include "FeatureExtractor.h"
#include "PixelCountFeature.h"

int main(int argc, char** argv)
{
	FeatureExtractor fe("C:/Temp/opirf/res", "features.arff", "relation");
	fe.addFeature(new PixelCountFeature(std::vector<std::string>()));
	
	fe.start();

	return 0;
}