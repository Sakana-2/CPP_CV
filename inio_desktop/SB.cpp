#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_Sobel_triggered() {
	ui.SBBox->show();
	ui.SBProcessing->hide();
}

void inio_desktop::on_SBExe_clicked() {
	ui.SBProcessing->show();
	repaint();

	img.sobel();

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.SBProcessing->hide();
}
