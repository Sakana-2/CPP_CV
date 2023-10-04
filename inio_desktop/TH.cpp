#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_Threshold_triggered() {
	ui.THBox->show();
	ui.THProcessing->hide();
	displayedBox.push_back(ui.THBox);
	PropBoxIncubator();
}

void inio_desktop::on_THExe_clicked() {
	ui.THProcessing->show();
	repaint();

	const uchar threshold = ui.THThreshold->value();

	img.threshold(threshold);

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.THProcessing->hide();
}
