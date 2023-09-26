#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_Laplacian_triggered() {
	ui.LPBox->show();
	ui.LPProcessing->hide();
}

void inio_desktop::on_LPExe_clicked() {
	ui.LPProcessing->show();
	repaint();

	img.laplacian(ui.LPis8->isChecked() ? LAPLACIAN_8 : LAPLACIAN_4);

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.LPProcessing->hide();
}
