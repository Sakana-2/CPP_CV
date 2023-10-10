#include "inio_desktop.h"
#include <qfiledialog.h>
#include <string>

#include "global.hpp"

inio_desktop::inio_desktop(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("Inio");
	ui.ImageLabel->setMinimumSize(1, 1);
	ui.BFBox->hide();
	ui.GFBox->hide();
	ui.PosterizeBox->hide();
	ui.CEBox->hide();
	ui.EHBox->hide();
	ui.GCBox->hide();
	ui.LPBox->hide();
	ui.PRBox->hide();
	ui.SBBox->hide();
	ui.MUBox->hide();
	ui.THBox->hide();
	ui.ATBox->hide();
	ui.INBox->hide();
	ui.core_2->hide();

	QPalette pal = palette();
	QColor color = QColor(70, 70, 70);
	pal.setColor(QPalette::Window, color);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	setStyleSheet("QLabel{color:white;}QGroupBox{ color:white;}QCheckBox{ color:white;}");
}

void inio_desktop::actionsEnabled() {
	QList<QMenu*> bars = ui.menuBar->findChildren<QMenu*>(QString(), Qt::FindChildrenRecursively);
	for (QMenu* bar : bars)
	{
		for (QAction* action : bar->actions())
		{
			action->setEnabled(true);
		}
	}
}

void inio_desktop::reload() {
	int w = ui.ImageLabel->width();
	int h = ui.ImageLabel->height();
	ui.ImageLabel->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void inio_desktop::resizeEvent(QResizeEvent* event) {
	reload();
}

void inio_desktop::on_Open_triggered() {
	QString filename = QFileDialog::getOpenFileName(
		this,
		tr("Open File"),
		"",
		tr("Images(*.jpg *.jpeg *.png)")
	);
	if (filename.isEmpty()) {
		return;
	}
	img.load(filename.toLocal8Bit().toStdString());
	setWindowTitle(filename);
	_pixmap = mat2qpixmap(img.get());
	reload();
	ui.alert->hide();
	ui.core_2->show();
	actionsEnabled();
	PropBoxIncubator();
}

void inio_desktop::on_Save_triggered() {
	img.save();
}

void inio_desktop::on_SaveAs_triggered() {
	QString filename = QFileDialog::getSaveFileName(
		this,
		tr("Open File"),
		"",
		tr("Images(*.jpg *.jpeg *.png)")
	);
	if (filename.isEmpty()) {
		return;
	}
	img.save(filename.toLocal8Bit().toStdString());
	setWindowTitle(filename);
};

void inio_desktop::on_Undo_triggered() {
	img.undo();
	_pixmap = mat2qpixmap(img.get());
	reload();
}

void inio_desktop::on_Redo_triggered() {
	img.redo();
	_pixmap = mat2qpixmap(img.get());
	reload();
}

void inio_desktop::on_Reset_triggered() {
	img.reset();
	_pixmap = mat2qpixmap(img.get());
	reload();
}

void inio_desktop::PropBoxIncubator() {
	if ((int)displayedBox.size() == 4) {
		displayedBox[0]->setVisible(false);
		displayedBox.erase(displayedBox.begin());
	}
}

inio_desktop::~inio_desktop()
{}