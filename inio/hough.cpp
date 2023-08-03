#include <vector>
#include <cmath>

#include "global.hpp"
#include "hough.hpp"

void HoughLines(cv::Mat src, double rho, double theta, int threshold) {
	double diagonal = std::sqrt(src.rows * src.rows + src.cols * src.cols);
	int numangle = std::nearbyint(PI / theta);
	int numrho = std::nearbyint((2 * diagonal) / rho);

	std::vector<double> tabSin,tabCos;
	CreateTrigTable(tabSin, tabCos,theta,numangle);

	cv::Mat accum = cv::Mat::zeros(numangle + 1, numrho + 1,CV_32SC1);

	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			if (row[j] != 0) {
				for (int n = 0; n < numangle; n++)
				{
					int r = std::nearbyint(j * tabSin[n] + i * tabCos[n]);
				}
			}
		}
	}
}

void CreateTrigTable(std::vector<double>& tabSin,std::vector<double>& tabCos,double theta, int numangle) {
	for (int i = 0; i < numangle; i++)
	{
		tabSin.push_back(std::sin(theta * i));
		tabCos.push_back(std::cos(theta * i));
	}
}