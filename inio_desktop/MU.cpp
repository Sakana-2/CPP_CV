#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_MeanUsm_triggered() {
	ui.MUBox->show();
	ui.MUProcessing->hide();
	displayedBox.push_back(ui.MUBox);
	PropBoxIncubator();
};

void inio_desktop::on_MUExe_clicked() {
	ui.MUProcessing->show();
	repaint();

	int blocksize = ui.MUBlockSize->value();
	double amount = ui.MUAmount->value();
	int adjustment = ui.MUAdjustment->value();

	if ((blocksize % 2) == 0) {
		blocksize -= 1;
	}

	img.unsharpmask_mean(blocksize,amount,adjustment);

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.MUProcessing->hide();
}
