#include "util.hpp"

#include <cmath>

cv::Mat mat_nearbyint(cv::Mat src) {
	cv::Mat dst = cv::Mat::zeros (src.rows, src.cols, CV_64FC1);
	for (int i = 0; i < src.rows; ++i)
	{
		double* row = src.ptr<double>(i);
		double* o_row = dst.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			o_row[j] = std::nearbyint(row[j]);
		}
	}
	return dst;
}

cv::Mat mat_clump(cv::Mat src) {
	cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_64FC1);
	for (int i = 0; i < dst.rows; ++i)
	{
		double* s_row = src.ptr<double>(i);
		double* o_row = dst.ptr<double>(i);
		for (int j = 0; j < dst.cols; ++j)
		{
			if (s_row[j] < 0) {
				o_row[j] = 0;
			}
			else if (s_row[j] > 255) {
				o_row[j] = 255;
			}
			else {
				o_row[j] = s_row[j];
			}
		}
	}
	return dst;
}

#ifdef NDEBUG
namespace py = pybind11;
py::dict mat2dict(cv::Mat src) {
	py::dict dst;
	dst["data"] = std::vector<double>(src.begin<double>(), src.end<double>());
	dst["rows"] = src.rows;
	dst["cols"] = src.cols;
	dst["ismono"] = (src.channels() == 1);
	return dst;
}

cv::Mat dict2mat(py::dict  src) {
	cv::Mat dst(src["rows"].cast<py::int_>(), src["cols"].cast<py::int_>(), src["ismono"].cast<py::bool_>() ? CV_64FC1 : CV_64FC3);
	for (int i = 0; i < src["rows"].cast<py::int_>(); i++)
	{
		py::list data = src["data"].cast<py::list>();
		if (src["ismono"].cast<py::bool_>()) {
			double* row = dst.ptr<double>(i);
			for (int j = 0; j < src["cols"].cast<py::int_>(); j++)
			{
				row[j] = data[i * src["cols"].cast<py::int_>() + j].cast<py::float_>();
			}
		}
		else {
			cv::Vec3d* row = dst.ptr<cv::Vec3d>(i);
			for (int j = 0; j < src["cols"].cast<py::int_>(); j += 3)
			{
				int base = i * src["cols"].cast<py::int_>() + j;
				
				row[j] = { data[base].cast<py::float_>(),data[base + 1].cast<py::float_>(),data[base + 2].cast<py::float_>() };
			}
		}
	}
	return dst;
}

#endif // NDEBUG