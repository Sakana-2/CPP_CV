#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_ContrastEmphasize_triggered() {
	ui.CEBox->show();
	ui.CEProcessing->hide();
}

void inio_desktop::on_CEExe_clicked() {
	ui.CEProcessing->show();
	repaint();

	const uchar imin = ui.CEIMin->value(),imax = ui.CEIMax->value(),omin = ui.CEOMin->value(),omax = ui.CEOMax->value();

	img.contrast_emphasizing(imin, imax, omin, omax);

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.CEProcessing->hide();
}
