#include "./unsharpmask.hpp"
#include "./border_prettier.hpp"

cv::Mat um(cv::Mat src, ushort blocksize, double k) {
	cv::Mat img = boder_replicate<uchar>(src, blocksize);
	cv::Mat dst(src.rows, src.cols, CV_8UC1, cv::Scalar::all(0));
	double half = (blocksize - 1) / 2;
	double bb = blocksize * blocksize;

	auto um_kernel = [img, blocksize, k, half, bb](int y, int x) {
		double sum = 0;
		for (int i = y - half; i < y + half + 1; ++i) {
			const uchar* row = img.ptr<uchar>(i);
			for (int j = x - half; j < x + half + 1; ++j) { //カーネルの左上から順に
				if ((i == y) && (j == x)) { //ど真ん中だったら

					sum += row[j] * (1 + ((bb - 1) * k / bb));
				}
				else { //外側だったら
					sum += row[j] * (-k / bb);
				}
			}
		}
		if (sum < 0) {
			sum = 0;
		}
		else if (sum > 255) {
			sum = 255;
		}
		return static_cast<uchar>(std::nearbyint(sum));
	};

	for (int i = 0; i < src.rows; ++i)
	{
		uchar* i_row = img.ptr<uchar>(i + half);
		uchar* o_row = src.ptr<uchar>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			o_row[j] = um_kernel(i + half, j + half);
		}
	}
	return src;
}