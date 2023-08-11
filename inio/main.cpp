#include <cmath>
#include <iostream>
#include <vector>

#include "main.hpp"
#include "contrast_emphasizing.hpp"
#include "edge_detection.hpp"
#include "equalize_hist.hpp"
#include "gamma_correction.hpp"
#include "global.hpp"
#include "grayscale.hpp"
#include "hough.hpp"
#include "layer.hpp"
#include "threshold.hpp"
#include "unsharpmask.hpp"
#include "util.hpp"
#include "posterization.hpp"

//TODO: 位相的データ解析（Topological Data Analysis）を使って線の認識

/*
WANNADO: 画像情報処理工学の前半を読む。
図形の検出について詳しく、scharrの実装、スクリーントーンの実装
*/


Inio::Inio(std::string path) {
	output_path = path;
	cv::Mat src, raw = cv::imread(path, cv::IMREAD_UNCHANGED); //TODO: Exifのorientationを参考に回転をかけないようにする
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

cv::Mat Inio::get() {
	return history.back();
}

void Inio::grayscale(double b, double g, double r) {
	history.push_back(gs(history.back(), b, g, r));
}

void Inio::houghLines(double rho, double theta, int threshold) {
	std::vector<line> lines;
	hl(history.back(), lines, rho, theta, threshold); //検出後の処理は今後作る
}

void Inio::laplacian(int mode) {
	history.push_back(_laplacian(history.back(), mode));
}

void Inio::multiply(Inio term) {
	history.push_back(mp(history.back(), term.get()));
}

void Inio::posterize(uchar level) {
	history.push_back(pz(history.back(), level));
}

void Inio::prewitt() {
	history.push_back(_prewitt(history.back()));
}

void Inio::save() {
	cv::imwrite(output_path, history.back());//TODO: historyの現在位置の(略)
}

void Inio::save(std::string another_path) {
	output_path = another_path;
	save();
}

void Inio::show() {
	cv::namedWindow(output_path, cv::WINDOW_NORMAL);
	cv::imshow(output_path, history.back());//TODO: あとで、タイトルを整形して代入するようにする historyの現在位置の画像を表示できるようにする。デフォルトのガンマ値を変えられるようにする
	cv::waitKey(0);
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

int main()
{
	return 0;
}