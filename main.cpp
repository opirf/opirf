//////////////////////////////////////////////////////////////////////////
// Module IRF, 5-iNFO
// Projet
//////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

//Croix pour position de ref
const Mat CROSS_Image = imread("images/templates/cross.png");


Point locateCrossSup(Mat m)
{
	Mat result;
	Point ptMax;

	// Extration du haut de la matrice image
	Mat subMat = m.rowRange(0, m.rows/3);

	// Localisation de la croix supérieure
	matchTemplate(subMat, CROSS_Image, result, CV_TM_CCOEFF_NORMED);
	minMaxLoc(result, NULL, NULL, NULL, &ptMax);

	// Position du centre de la croix
	ptMax.x += 63;
	ptMax.y += 58;

	return ptMax;
}


Point locateCrossSub(Mat m)
{
	Mat result;
	Point ptMax;

	// Extration du haut de la matrice image
	Mat subMat = m.rowRange(2*m.rows/3, m.rows);

	// Localisation de la croix supérieure
	matchTemplate(subMat, CROSS_Image, result, CV_TM_CCOEFF_NORMED);
	minMaxLoc(result, NULL, NULL, NULL, &ptMax);

	// Position du centre de la croix
	ptMax.x += 63;
	ptMax.y += 58 + 2*m.rows/3;

	return ptMax;
}

int main (int argc, char** argv) {

	stringstream ss;

	

	for(int i=0;i<10;++i) {
		try{
		stringstream ss;
		ss << "images/database/w000-scans/0000";
		ss << i << ".png";

		cout << ss.str() << endl;
		Mat image = imread(ss.str());

		Point p1 = locateCrossSup(image);
		Point p2 = locateCrossSub(image);

		cout << "Sup cross position : x:" << p1.x << ", y:" << p1.y << endl;
		cout << "Sub cross position : x:" << p2.x << ", y:" << p2.y << endl;
		} catch(std::exception &e) {
			cout<<e.what();
		}

	}

	system("pause");
}
