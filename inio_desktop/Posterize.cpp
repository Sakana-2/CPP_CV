#include "inio_desktop.h"
#include "global.hpp"

void inio_desktop::on_Posterize_triggered() {
	ui.PosterizeBox->show();
	ui.PosterizeProcessing->hide();
	displayedBox.push_back(ui.PosterizeBox);
	PropBoxIncubator();
}

void inio_desktop::on_PosterizeExe_clicked() {
	ui.PosterizeProcessing->show();
	repaint();

	const uchar level = ui.PosterizeLevel->value();

	img.posterize(level);

	_pixmap = mat2qpixmap(img.get());
	reload();

	ui.PosterizeProcessing->hide();
}
