#include <vector>
#include <opencv2/opencv.hpp>

class Inio
{
	cv::Mat src;
	std::string output_path;
	std::vector<cv::Mat> history; //ƒ|ƒCƒ“ƒ^‚Ì•Û‘¶‚Ì•û‚ª‘‚¢‚©‚à‚µ‚ê‚È‚¢
public:
	Inio(std::string path);
	void grayscale(double b = 0.0722, double g = 0.7152, double r = 0.2126);
	void equalize_hist();
	void threshold(uchar thresh);
	void show();
	void save();
	void save(std::string another_path);
};