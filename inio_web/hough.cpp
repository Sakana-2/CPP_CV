#include <algorithm>
#include <cmath>
#include <vector>

#include "global.hpp"
#include "hough.hpp"

void CreateTrigTable(std::vector<double>& tabSin, std::vector<double>& tabCos, double theta, int numangle, double rho) {
	for (int i = 0; i < numangle; i++)
	{
		tabSin.push_back(std::sin(theta * i) / rho);
		tabCos.push_back(std::cos(theta * i) / rho);
	}
}

void findLocalMaximum(int numrho, int numangle, int threshold, const int* accum, std::vector<int>& lm_indices) {
	for (int i = 0; i < numangle; i++)
	{
		for (int j = 0; j < numrho; j++)
		{
			int base = (i + 1) * (numrho + 2) + j + 1;
			if ((accum[base] > accum[base - 1]) && (accum[base] >= accum[base + 1]) && (accum[base] > accum[base - (numrho + 2)]) && (accum[base] >= accum[base + (numrho + 2)])) {
				lm_indices.push_back(base);
			}
		}
	}

}

struct hough_greater
{
	const int* accum;
	hough_greater(const int* _accum):accum(_accum) {}
	inline bool operator()(int i1, int i2) {
		return (accum[i1] > accum[i2]) || ((accum[i1] == accum[i2] && i1 < i2));
	}
};

void hl(cv::Mat src, std::vector<line>& lines, double rho, double theta, int threshold) {
	int numangle = std::nearbyint(PI / theta); //�v�Z����p�x�̎�ނ̐�
	int numrho = std::nearbyint((2 * (src.rows + src.cols)) / rho); //�v�Z���鋗���̎�ނ̐�

	std::vector<double> tabSin,tabCos;
	CreateTrigTable(tabSin, tabCos, theta, numangle, rho); //�g�p����T�C���ƃR�T�C���̒l�����O�Ɍv�Z����

	cv::Mat _accum = cv::Mat::zeros(numangle + 2, numrho + 2, CV_32SC1); //+2����̂̓t�B���^�[��������Ƃ��̂��߂̃p�f�B���O����
	int* accum = _accum.ptr<int>();

	//���[
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			double* row = src.ptr<double>(i);
			if (row[j] != 0) {
				for (int n = 0; n < numangle; n++)
				{
					int r = std::nearbyint(j * tabSin[n] + i * tabCos[n]);
					r += std::nearbyint(numrho / 2);
					accum[(n+1) * (numrho + 2) + r + 1]++;
				}
			}
		}
	}

	//theta�����Arho�����̂ǂ���ɂ����Ă��ɑ�l�ƂȂ�g�ݍ��킹�݂̂��Ƃ肾���āA�ގ���������폜����
	std::vector<int> lm_indices;
	findLocalMaximum(numrho, numangle, threshold, accum, lm_indices);

	//�擾�����C���f�b�N�X�ꗗ��accum�̒l�����Ƃɍ~���ɂ���
	std::sort(lm_indices.begin(), lm_indices.end(), hough_greater(accum));

	for (int index : lm_indices)
	{
		double w = theta * ((index / (numrho + 2)) - 1);
		double d = rho * (((index % (numrho + 2)) - 1) - (int)std::nearbyint(numrho / 2));
		lines.push_back({ w,d });
	}
}

