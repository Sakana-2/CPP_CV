#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <iostream>

#include "main.hpp"
#include "contrast_emphasizing.hpp"
#include "edge_detection.hpp"
#include "equalize_hist.hpp"
#include "gaussian_blur.hpp"
#include "gamma_correction.hpp"
#include "grayscale.hpp"
#include "hough.hpp"
#include "invert.hpp"
#include "layer.hpp"
#include "threshold.hpp"
#include "unsharpmask.hpp"
#include "util.hpp"
#include "posterization.hpp"

//TODO: 位相的データ解析（Topological Data Analysis）を使って線の認識

/*
TODO: ハフ変換の続き、scharrの実装、スクリーントーンの実装
*/

namespace py = pybind11;
PYBIND11_MODULE(inio_web, m) {
	py::class_<Inio>(m, "Inio")
		.def(py::init<py::dict>())
		.def("adaptive_threshold_mean", &Inio::adaptive_threshold_mean)
		.def("contrast_emphasizing", &Inio::contrast_emphasizing)
		.def("equalize_hist", &Inio::equalize_hist)
		.def("gamma_correction", &Inio::gamma_correction)
		.def("gaussian_blur", &Inio::gaussisn_blur)
		.def("get", &Inio::get)
		.def("grayscale", &Inio::grayscale)
		.def("houghLines", &Inio::houghLines)
		.def("invert",&Inio::invert)
		.def("laplacian", &Inio::laplacian)
		.def("multiply", &Inio::multiply)
		.def("posterize", &Inio::posterize)
		.def("prewitt", &Inio::prewitt)
		.def("threshold", &Inio::threshold)
		.def("unsharpmask_lap", &Inio::unsharpmask_lap)
		.def("unsharpmask_mean", &Inio::unsharpmask_mean)
		;
}

Inio::Inio(py::dict asset) {

	cv::Mat src, raw = dict2mat(asset);
	switch (raw.type())
	{
	case CV_8UC3:
		raw.convertTo(src, CV_64FC3);
		break;
	case CV_8UC1:
		raw.convertTo(src, CV_64FC1);
		break;
	default:
		std::cout << "Not Supported " << raw.type() << std::endl;
		std::exit(0);
		break;
	}
	history.push_back(src);

}

void Inio::adaptive_threshold_mean(ushort blocksize, uchar c) {
	history.push_back(ad_th_mean(history.back(), blocksize, c));
}

void Inio::contrast_emphasizing(uchar i_min, uchar i_max, uchar o_min, uchar o_max) {
	history.push_back(ce(history.back(), i_min, i_max, o_min, o_max));
}

void Inio::equalize_hist() {
	history.push_back(eh(history.back()));
}

/*
* TODO:
ディスプレイやOSによってガンマ補正をかけるかどうかを判定したうえで使う。
*/
void Inio::gamma_correction(double ganma) {
	history.push_back(gc(history.back(), ganma));
}

void Inio::gaussisn_blur(ushort blocksize,double sigma) {
	history.push_back(gblur(history.back(), blocksize, sigma));
}

py::dict Inio::get() {
	return mat2dict(history.back());
}

void Inio::grayscale(double b, double g, double r) {
	history.push_back(gs(history.back(), b, g, r));
}

void Inio::houghLines(double rho, double theta, int threshold) {
	std::vector<line> lines;
	hl(history.back(), lines, rho, theta, threshold); //検出後の処理は今後作る
}

void Inio::invert() {
	history.push_back(invrt(history.back()));
}

void Inio::laplacian(int mode) {
	history.push_back(_laplacian(history.back(), mode));
}

void Inio::multiply(Inio term) {
	history.push_back(mp(history.back(), dict2mat(term.get())));
}

void Inio::posterize(uchar level) {
	history.push_back(pz(history.back(), level));
}

void Inio::prewitt() {
	history.push_back(_prewitt(history.back()));
}

void Inio::sobel() {
	history.push_back(_sobel(history.back()));
}

void Inio::threshold(uchar thresh) {
	history.push_back(th(history.back(), thresh));
}

void Inio::unsharpmask_lap(int laplacian_mode, double k, int c) {
	//std::cout << um_laplacian(history.back(), laplacian_mode, k, c) << std::endl;
	history.push_back(um_laplacian(history.back(), laplacian_mode, k, c));
}

void Inio::unsharpmask_mean(ushort blocksize, double k, int c) {
	history.push_back(um_mean(history.back(), blocksize, k, c));
	//カラー画像の時はhsl色空間に変換する
}