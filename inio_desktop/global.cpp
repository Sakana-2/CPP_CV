#include "global.hpp"

QPixmap mat2qpixmap(cv::Mat data) {
	cv::Mat src;
	if (data.type() == 6) {
		data.convertTo(data, CV_8UC1);
		cv::cvtColor(data, src, cv::COLOR_GRAY2BGR);
	}
	else {
		data.convertTo(data, CV_8UC3);
		src = data;
	}

	return QPixmap::fromImage(QImage(src.data, src.cols, src.rows, src.step, QImage::Format_BGR888));
}