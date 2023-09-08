#include "inio_desktop.h"
#include <qfiledialog.h>

inio_desktop::inio_desktop(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.ImageLabel->setMinimumSize(1, 1);
}

void inio_desktop::actionsEnabled() {
	QList<QMenu*> bars = ui.menuBar->findChildren<QMenu*>(QString(), Qt::FindDirectChildrenOnly);
	for (QMenu* bar : bars)
	{
		for (QAction* action : bar->actions())
		{
			action->setEnabled(true);
		}
	}
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
	reload();
	actionsEnabled();
}

void inio_desktop::reload() {
	cv::Mat src;
	cv::Mat data = img.get();
	if (data.type() == 6) {
		data.convertTo(data,CV_8UC1);
		cv::cvtColor(data, src, cv::COLOR_GRAY2BGR);
	}
	else {
		data.convertTo(data, CV_8UC3);
		src = data;
	}
	
	_qpixmap = QPixmap::fromImage(QImage(src.data, src.cols, src.rows, src.step, QImage::Format_BGR888));
	displayImage();
}

void inio_desktop::displayImage() {
	int w = ui.ImageLabel->width();
	int h = ui.ImageLabel->height();
	ui.ImageLabel->setPixmap(_qpixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void inio_desktop::resizeEvent(QResizeEvent* event) {
	displayImage();
}

inio_desktop::~inio_desktop()
{}