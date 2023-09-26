#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_Prewitt_triggered() {
	ui.LPBox->show();
	ui.LPProcessing->hide();
}

void inio_desktop::on_PRExe_clicked() {
	ui.PRProcessing->show();
	repaint();

	img.prewitt();

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.PRProcessing->hide();
}
