#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_BDither_triggered() {
	ui.BDBox->show();
	ui.BDProcessing->hide();
	displayedBox.push_back(ui.BDBox);
	PropBoxIncubator();
}

void inio_desktop:: on_BDExe_clicked() {
	ui.BDProcessing->show();
	repaint();

	int grad_num = ui.BDGrad->currentIndex();

	switch (grad_num)
	{
	case 0:
		img.bayer(2);
		break;
	case 1:
		img.bayer(4);
		break;
	case 2:
		img.bayer(8);
		break;
	case 3:
		img.bayer(16);
		break;
	default:
		break;
	}

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.BDProcessing->hide();
}