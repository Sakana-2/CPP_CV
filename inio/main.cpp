#include <iostream>

#include "main.hpp"
#include "gamma_correction.hpp"
#include "grayscale.hpp"
#include "equalize_hist.hpp"
#include "threshold.hpp"
#include "unsharpmask.hpp"

//�����_�֐����g���ē����l�̈����𖈉���͂��邱�Ƃ������

Inio::Inio(std::string path) {
	output_path = path;
	cv::Mat src;
	cv::imread(path).convertTo(src, CV_64FC3);
	history.push_back(src);
}

void Inio::adaptive_threshold(ushort blocksize, uchar c) {
	if (history.back().type() == CV_64FC3) {
		history.push_back(ad_th_mean(gs(history.back()), blocksize, c));
	}
	else {
		history.push_back(ad_th_mean(history.back(), blocksize, c));
	}
	
}

void Inio::equalize_hist() {
	history.push_back(eh(history.back()));
}

void Inio::gamma_correction(double ganma) {
	history.push_back(gc(history.back(), ganma));
}

void Inio::grayscale(double b, double g, double r) {
	history.push_back(gs(history.back(), b, g, r));
}

void Inio::save() {
	cv::imwrite(output_path, history.back());//history�̌��݈ʒu��(��)
}

void Inio::save(std::string another_path) {
	output_path = another_path;
	save();
}

void Inio::show() {
	cv::namedWindow(output_path, cv::WINDOW_NORMAL);
	cv::imshow(output_path, history.back());//���ƂŁA�^�C�g���𐮌`���đ������悤�ɂ��� history�̌��݈ʒu�̉摜��\���ł���悤�ɂ���B�f�t�H���g�̃K���}�l��ς�����悤�ɂ���
	cv::waitKey(0);
}

void Inio::threshold(uchar thresh) {
	history.push_back(th(history.back(), thresh));
}

void Inio::unsharpmask(ushort blocksize, int k) {
	history.push_back(um(history.back(), blocksize, k));
	//�J���[�摜�̎���hsl�F��Ԃɕϊ�����
}

int main()
{
	return 0;
}