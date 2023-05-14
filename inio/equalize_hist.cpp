#include <iostream>

#include "equalize_hist.hpp"

cv::Mat eh(cv::Mat src) {
	unsigned int hist[256] = {}, cumsum[256] = {};
	//�q�X�g�O����
	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			hist[static_cast<int>(row[j])] += 1;
		}
	}
	/*
	�ݐϘa�����߂�
	0�̎��������������̂�C++����-1���C���f�b�N�X�ɂł��Ȃ�����
	*/
	cumsum[0] = hist[0];
	for (int i=1; i<256;++i)
	{
		cumsum[i] = cumsum[i - 1] + hist[i];
	}
	double size = cumsum[255];
	//�ݐϘa�𒼐���ɐ��`
	for (int i = 0; i < 256; ++i) {
		cumsum[i] = std::nearbyint(cumsum[i] * 255 / size);
	}
	//�l��u�����Ă���
	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			row[j] = cumsum[static_cast<int>(row[j])];
		}
	}
	return src;
}