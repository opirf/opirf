#include "FeatureExtractor.h"
#include "PixelCountFeature.h"

int main(int argc, char** argv)
{
	FeatureExtractor fe(argv[1], "features.arff", "relation");
	fe.addFeature(new PixelCountFeature());
	
	fe.start();

	return 0;
}