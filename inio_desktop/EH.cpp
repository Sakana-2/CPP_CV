#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_EquHist_triggered() {
	ui.EHBox->show();
	ui.EHProcessing->hide();
}

void inio_desktop::on_EHExe_clicked() {
	ui.EHProcessing->show();
	repaint();

	img.equalize_hist();

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.EHProcessing->hide();
}
