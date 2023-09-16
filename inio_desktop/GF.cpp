#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_GaussianFilter_triggered() {
	qDebug() << "Ganbare";
	ui.GFBox->show();
	ui.GFProcessing->hide();
};

void inio_desktop::on_GFExe_clicked() {
	ui.GFProcessing->show();
	repaint();

	int blocksize = ui.GFBlockSize->value();
	double sigma = ui.GFSigma->value();

	if ((blocksize % 2) == 0) {
		blocksize -= 1;
	}

	img.gaussisn_blur(blocksize,sigma);

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.GFProcessing->hide();
}
