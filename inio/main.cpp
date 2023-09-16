#include <iostream>

#include "main.hpp"
#include "box_filter.hpp"
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

void Inio::load(std::string path) {
	output_path = path;
	load(cv::imread(path, cv::IMREAD_COLOR));
}

void Inio::load(cv::Mat raw) {
	cv::Mat src;
	raw.convertTo(src, CV_64FC3);
	history.clear();
	if (isfakegray(src)) {
		this->set(make_realgray(src));
	}
	else {
		this->set(src);
	}
}

void Inio::adaptive_threshold_mean(ushort blocksize, uchar c) {
	this->set(ad_th_mean(this->get(), blocksize, c));
}

void Inio::box_filter(ushort blocksize) {
	this->set(bf(this->get(), blocksize));
}

void Inio::contrast_emphasizing(uchar i_min, uchar i_max, uchar o_min, uchar o_max) {
	this->set(ce(this->get(), i_min, i_max, o_min, o_max));
}

void Inio::equalize_hist() {
	this->set(eh(this->get()));
}

/*
* TODO:
ディスプレイやOSによってガンマ補正をかけるかどうかを判定したうえで使う。
*/
void Inio::gamma_correction(double ganma) {
	this->set(gc(this->get(), ganma));
}

void Inio::gaussisn_blur(ushort blocksize,double sigma) {
	this->set(gblur(this->get(), blocksize, sigma));
}

cv::Mat Inio::get() {
	return history[(int)history.size() - index].clone();
}

void Inio::grayscale(double b, double g, double r) {
	this->set(gs(this->get(), b, g, r));
}

void Inio::houghLines(double rho, double theta, int threshold) {
	std::vector<line> lines;
	hl(this->get(), lines, rho, theta, threshold); //検出後の処理は今後作る
}

void Inio::invert() {
	this->set(invrt(this->get()));
}

void Inio::laplacian(int mode) {
	this->set(_laplacian(this->get(), mode));
}

void Inio::multiply(Inio term) {
	this->set(mp(this->get(), term.get()));
}

void Inio::posterize(uchar level) {
	this->set(pz(this->get(), level));
}

void Inio::prewitt() {
	this->set(_prewitt(this->get()));
}

void Inio::redo() {
	if (index > 0) {
		index--;
	}
}

void Inio::save() {
	cv::imwrite(output_path, this->get());//TODO: historyの現在位置の(略)
}

void Inio::save(std::string another_path) {
	output_path = another_path;
	save();
}

void Inio::set(cv::Mat src) {
	if (index != 0)
	{
		history.erase(history.end() - index, history.end());
	}
	history.push_back(src);
}

void Inio::show() {
	cv::namedWindow(output_path, cv::WINDOW_NORMAL);
	cv::imshow(output_path, this->get());//TODO: あとで、タイトルを整形して代入するようにする historyの現在位置の画像を表示できるようにする。デフォルトのガンマ値を変えられるようにする
	cv::waitKey(0);
}

void Inio::sobel() {
	this->set(_sobel(this->get()));
}

void Inio::threshold(uchar thresh) {
	this->set(th(this->get(), thresh));
}

void Inio::undo() {
	if (((int)history.size()-1) > index)
	{
		index++;
	}
}

void Inio::unsharpmask_lap(int laplacian_mode, double k, int c) {
	this->set(um_laplacian(this->get(), laplacian_mode, k, c));
}

void Inio::unsharpmask_mean(ushort blocksize, double k, int c) {
	this->set(um_mean(this->get(), blocksize, k, c));
	//カラー画像の時はhsl色空間に変換する
}