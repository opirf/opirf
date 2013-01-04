#include "HistogramPeaksFeature.h"
#include "Logger.h"

std::vector<double> HistogramPeaksFeature::featureApply(const cv::Mat& imageRaw, const cv::Mat& imageNorm, const cv::Mat& imageNormBin, const cv::Rect& boundingBox)
{
	std::vector<double> ret;

	// Ceation of the histogram
	std::vector<int>* histo;
	int rangeIndice, histoSize;
	

	unsigned char *input = (unsigned char*)(imageNormBin.data);

	if(_orientation == VERTICAL) {
		histoSize = (int)(imageNormBin.cols/_pixelRange)+1;
		histo = new std::vector<int>(histoSize, 0);

		for(int i=0; i<imageNormBin.cols; ++i) {
			rangeIndice = (int)(i/_pixelRange);
			for(int j=0; j<imageNormBin.rows; ++j) {
				if(input[imageNormBin.step*i+j]==0) {
					(*histo)[rangeIndice]++;
				}
			}
		}
	} else {
		histoSize = (int)(imageNormBin.rows/_pixelRange)+1;
		histo = new std::vector<int>(histoSize, 0);

		for(int i=0; i<imageNormBin.rows; ++i) {
			rangeIndice = (int)(i/_pixelRange);
			for(int j=0; j<imageNormBin.cols; ++j) {
				if(input[imageNormBin.step*j+i]==0) {
					(*histo)[rangeIndice]++;
				}
			}
		}
	}


	// Couting number of peaks in the histogram
	int minPeakPos, maxPeakPos, nbPeak, maxVal, maxPos;
	bool stop, found;

	nbPeak = 0;
	maxVal = -1;
	maxPos = -1;
	for(int i=0;i<histoSize; ++i) {

		if((*histo)[i]>maxVal) {maxVal = (*histo)[i]; maxPos = i;}

		stop = false;
		found = false;
		for(int j=1;j<=_peakRange&&!stop;++j) {
			minPeakPos = (i-j+histoSize)%histoSize;

			if((*histo)[minPeakPos]<(*histo)[i] && (*histo)[minPeakPos]+(*histo)[minPeakPos] * _peakMinGap <= (*histo)[i]) {
				stop = true;
				found = true;
			}
		}

		if(found) {
			stop = false;
			for(int j=1;j<=_peakRange&&!stop;++j) {
				maxPeakPos = (i+j)%histoSize;

				if((*histo)[maxPeakPos]<(*histo)[i] && (*histo)[maxPeakPos]+(*histo)[maxPeakPos] * _peakMinGap <= (*histo)[i]) {
					++nbPeak;
					i += j;
					stop = true;
				}
			}
		}
	}

	// display histogram && data
	/*for(int i=0; i<histoSize; ++i) {
		std::cout << (*histo)[i] << ";";
	}

	std::cout << "\n nbPeak:" << nbPeak << ", maxPos:" << maxPos << std::endl;
	cv::imshow("haa", imageNormBin);
	
	int scale = 7;
    cv::Mat histImg = cv::Mat(maxVal/scale, histoSize*5, CV_8UC3, cv::Scalar(255,255,255));

    for(int i=0;i<histoSize; ++i) {
        cv::rectangle(	histImg,
						cv::Point(i*5, (maxVal-(*histo)[i])/scale),
                        cv::Point(i*5+3, maxVal/scale),
                        cv::Scalar(0,0,0),
                        CV_FILLED);

	}
	cv::imshow( "H-S Histogram", histImg);
	cv::waitKey(0);*/
	
	ret.push_back(nbPeak);
	ret.push_back(maxPos);
	delete histo;
	return ret;
}