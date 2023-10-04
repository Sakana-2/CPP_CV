#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_AdaptiveThreshold_triggered() {
	ui.ATBox->show();
	ui.ATProcessing->hide();
	displayedBox.push_back(ui.ATBox);
	PropBoxIncubator();
};

void inio_desktop::on_ATExe_clicked() {
	ui.ATProcessing->show();
	repaint();

	int blocksize = ui.ATBlockSize->value();
	int adjustment = ui.ATAdjustment->value();

	if ((blocksize % 2) == 0) {
		blocksize -= 1;
	}

	img.adaptive_threshold_mean(blocksize, adjustment);

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.ATProcessing->hide();
}
