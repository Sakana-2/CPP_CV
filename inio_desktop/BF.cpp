#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_BoxFilter_triggered() {
	ui.BoxFilterBox->show();
	ui.BFProcessing->hide();
};

void inio_desktop::on_BFExe_clicked() {
	ui.BFProcessing->show();
	repaint();

	int value = ui.BFBlockSize->value();

	if ((value % 2) == 0) {
		value -= 1;
	}

	preview.load(img.get());
	preview.box_filter(value);

	_qpixmap = mat2qpixmap(preview.get());
	reload();

	ui.BFProcessing->hide();
}
