#pragma once

#include <opencv2/opencv.hpp>

//TODO: 端の処理の種類を増やすべきか調べる

cv::Mat border_replicate(cv::Mat src, ushort blocksize);