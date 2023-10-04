#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_Invert_triggered() {
	ui.INBox->show();
	ui.INProcessing->hide();
	displayedBox.push_back(ui.INBox);
	PropBoxIncubator();
}

void inio_desktop::on_INExe_clicked() {
	ui.INProcessing->show();
	repaint();

	img.invert();

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.INProcessing->hide();
}
