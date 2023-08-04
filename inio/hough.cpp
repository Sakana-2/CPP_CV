#include <vector>
#include <cmath>

#include "global.hpp"
#include "hough.hpp"

void CreateTrigTable(std::vector<double>& tabSin, std::vector<double>& tabCos, double theta, int numangle, double rho) {
	for (int i = 0; i < numangle; i++)
	{
		tabSin.push_back(std::sin(theta * i) / rho);
		tabCos.push_back(std::cos(theta * i) / rho);
	}
}

void hl(cv::Mat src, double rho, double theta, int threshold) {
	const double diagonal = std::sqrt(src.rows * src.rows + src.cols * src.cols);
	int numangle = std::nearbyint(PI / theta); //�v�Z����p�x�̎�ނ̐�
	int numrho = std::nearbyint((2 * diagonal) / rho); //�v�Z���鋗���̎�ނ̐�

	std::vector<double> tabSin,tabCos;
	CreateTrigTable(tabSin, tabCos, theta, numangle, rho); //�g�p����T�C���ƃR�T�C���̒l�����O�Ɍv�Z����

	cv::Mat accum = cv::Mat::zeros(numangle + 2, numrho + 2, CV_32SC1); //�[�̕�������Ȃ�����+1,�l�̌ܓ��̂Ƃ��̌덷�p�ɂ���+1

	//���[
	for (int i = 0; i < src.rows; i++)
	{
		double* row = src.ptr<double>(i);
		for (int j = 0; j < src.cols; j++)
		{
			if (row[j] != 0) {
				
				for (int n = 0; n < numangle; n++)
				{
					int r = std::nearbyint(j * tabSin[n] + i * tabCos[n]);
					r += numrho / 2;

					int* accum_row = accum.ptr<int>(n);
					accum_row[r]++;
				}
			}
		}
	}
}

