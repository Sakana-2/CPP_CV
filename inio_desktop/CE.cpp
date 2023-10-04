#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_ContrastEmphasize_triggered() {
	ui.CEBox->show();
	ui.CEProcessing->hide();
	displayedBox.push_back(ui.CEBox);
	PropBoxIncubator();
}

void inio_desktop::on_CEExe_clicked() {
	ui.CEProcessing->show();
	repaint();

	uchar imin = ui.CEIMin->value(),imax = ui.CEIMax->value(),omin = ui.CEOMin->value(),omax = ui.CEOMax->value();

	if (imin >= imax) {
		imax = imin + 1;
		ui.CEIMax->setValue(imax);
	}
	if (omin >= omax)
	{
		omax = omin + 1;
		ui.CEOMax->setValue(omax);
	}

	img.contrast_emphasizing(imin, imax, omin, omax);

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.CEProcessing->hide();
}
