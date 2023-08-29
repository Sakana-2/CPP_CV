#include "inio_desktop.h"
#include <qfiledialog.h>

inio_desktop::inio_desktop(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void inio_desktop::on_Open_triggered() {
	QString filename = QFileDialog::getOpenFileName(
		this,
		tr("Open File"),
		"",
		tr("Images(*.jpg *.jpeg *.png)")
	);

}

inio_desktop::~inio_desktop()
{}