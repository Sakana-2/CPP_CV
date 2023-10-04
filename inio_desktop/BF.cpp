#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_BoxFilter_triggered() {
	ui.BFBox->show();
	ui.BFProcessing->hide();
	displayedBox.push_back(ui.BFBox);
	PropBoxIncubator();
};

void inio_desktop::on_BFExe_clicked() {
	ui.BFProcessing->show();
	repaint();

	int value = ui.BFBlockSize->value();

	if ((value % 2) == 0) {
		value -= 1;
	}

	img.box_filter(value);

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.BFProcessing->hide();
}
