#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_LaplUsm_triggered() {
	qDebug() << "AIUEO";
	ui.LUBox->show();
	ui.LUProcessing->hide();
	displayedBox.push_back(ui.LUBox);
	PropBoxIncubator();
}

void inio_desktop::on_LUExe_clicked() {
	ui.LUProcessing->show();
	repaint();

	int blocksize = ui.LUBlockSize->value();
	double amount = ui.LUAmount->value();
	int adjustment = ui.LUAdjustment->value();

	if ((blocksize % 2) == 0) {
		blocksize -= 1;
	}

	img.unsharpmask_mean(blocksize, amount, adjustment);

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.LUProcessing->hide();
}
