#include <vector>
#include <opencv2/opencv.hpp>

class Inio
{
	cv::Mat src;
	std::string output_path;
	std::vector<cv::Mat> history; //ƒ|ƒCƒ“ƒ^‚Ì•Û‘¶‚Ì•û‚ª‘‚¢‚©‚à‚µ‚ê‚È‚¢
public:
	Inio(std::string path);
	void ganma_correction(float ganma = 2.2f);
	void grayscale(double b = 0.0722, double g = 0.7152, double r = 0.2126);
	void equalize_hist();
	void save();
	void save(std::string another_path);
	void show();
	void threshold(uchar thresh);
	
};