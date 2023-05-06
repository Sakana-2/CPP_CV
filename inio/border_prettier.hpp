#pragma once

#include <opencv2/opencv.hpp>

template <typename T>
cv::Mat boder_replicate(cv::Mat src, ushort blocksize) {
	cv::Mat dst(src.cols + blocksize - 1, src.rows + blocksize - 1, src.type(), cv::Scalar::all(0));
	ushort half = (blocksize - 1) / 2;
	ushort c_last = src.cols - 1; //画像の縦横の最後のインデックス
	ushort r_last = src.rows - 1;
	for (int i = 0; i < dst.rows; ++i)
	{
		T* d_row = dst.ptr<T>(i);
		for (int j = 0; j < dst.cols; ++j)
		{
			bool istop = i < half;
			bool isbottom = i > dst.rows - half - 1;
			bool isleft = j < half;
			bool isright = j > dst.cols - half - 1;
			if (istop && isleft) { //左上
				T* p = src.ptr<T>(0);
				d_row[j] = p[0];
			}
			else if (istop && isright) { //右上
				T* p = src.ptr<T>(0);
				d_row[j] = p[c_last];
			}
			else if (isbottom && isleft) { //左下
				T* p = src.ptr<T>(r_last);
				d_row[j] = p[0];
			}
			else if (isbottom && isright) { //右下
				T* p = src.ptr<T>(r_last);
				d_row[j] = p[c_last];
			}
			else if (istop && !isleft && !isright) { //上中間
				T* p = src.ptr<T>(0);
				d_row[j] = p[j - half];
			}
			else if (isleft && !istop && !isbottom) { //左中間
				T* p = src.ptr<T>(i - half);
				d_row[j] = p[0];
			}
			else if (isright && !istop && !isbottom) { //右中間
				T* p = src.ptr<T>(i - half);
				d_row[j] = p[c_last];
			}
			else if (isbottom && !isleft && !isright) { //下中間
				T* p = src.ptr<T>(r_last);
				d_row[j] = p[j - half];
			}
			else { //真ん中
				T* p = src.ptr<T>(i - half);
				d_row[j] = p[j - half];
			}
		}
	}

	return dst;
}