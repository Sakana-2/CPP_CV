#include <vector>
#include <opencv2/opencv.hpp>

class Inio
{
	std::string output_path;
	std::vector<cv::Mat> history; //ポインタの保存の方が早いかもしれない
public:
	Inio(std::string path);
	void adaptive_threshold(ushort blocksize, uchar c);
	void equalize_hist();
	void gamma_correction(double ganma = 2.2);
	void grayscale(double b = 0.0722, double g = 0.7152, double r = 0.2126);
	void save();
	void save(std::string another_path);
	void show();
	void threshold(uchar thresh);
	void unsharpmask(ushort blocksize, int k);
	
};