#pragma once

#include <opencv2/opencv.hpp>

//TODO: �[�̏����̎�ނ𑝂₷�ׂ������ׂ�

cv::Mat border_replicate(cv::Mat src, ushort blocksize) {
	cv::Mat dst(src.rows + blocksize - 1, src.cols + blocksize - 1, CV_64FC1, cv::Scalar::all(0));
	ushort half = (blocksize - 1) / 2;
	ushort c_last = src.cols - 1; //�摜�̏c���̍Ō�̃C���f�b�N�X
	ushort r_last = src.rows - 1;
	for (int i = 0; i < dst.rows; ++i)
	{
		double* d_row = dst.ptr<double>(i);
		for (int j = 0; j < dst.cols; ++j)
		{
			bool istop = i < half;
			bool isbottom = i > dst.rows - half - 1;
			bool isleft = j < half;
			bool isright = j > dst.cols - half - 1;
			if (istop && isleft) { //����
				double* p = src.ptr<double>(0);
				d_row[j] = p[0];
			}
			else if (istop && isright) { //�E��
				double* p = src.ptr<double>(0);
				d_row[j] = p[c_last];
			}
			else if (isbottom && isleft) { //����
				double* p = src.ptr<double>(r_last);
				d_row[j] = p[0];
			}
			else if (isbottom && isright) { //�E��
				double* p = src.ptr<double>(r_last);
				d_row[j] = p[c_last];
			}
			else if (istop && !isleft && !isright) { //�㒆��
				double* p = src.ptr<double>(0);
				d_row[j] = p[j - half];
			}
			else if (isleft && !istop && !isbottom) { //������
				double* p = src.ptr<double>(i - half);
				d_row[j] = p[0];
			}
			else if (isright && !istop && !isbottom) { //�E����
				double* p = src.ptr<double>(i - half);
				d_row[j] = p[c_last];
			}
			else if (isbottom && !isleft && !isright) { //������
				double* p = src.ptr<double>(r_last);
				d_row[j] = p[j - half];
			}
			else { //�^��
				double* p = src.ptr<double>(i - half);
				d_row[j] = p[j - half];
			}
		}
	}

	return dst;
}