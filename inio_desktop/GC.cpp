#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_GammaCorrection_triggered() {
	ui.GCBox->show();
	ui.GCProcessing->hide();
	displayedBox.push_back(ui.GCBox);
	PropBoxIncubator();
}

void inio_desktop::on_GCExe_clicked() {
	ui.GCProcessing->show();
	repaint();

	img.gamma_correction(ui.GCGamma->value());

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.GCProcessing->hide();
}
