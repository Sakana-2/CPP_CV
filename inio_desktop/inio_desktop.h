#pragma once

#include <QtWidgets/QMainWindow>
#include <qpixmap.h>
#include <qgraphicsscene.h>
#include <opencv2/opencv.hpp>
#include "ui_inio_desktop.h"
#include "../inio/main.hpp"

class inio_desktop : public QMainWindow
{
	Q_OBJECT

public:
	inio_desktop(QWidget *parent = nullptr);
	~inio_desktop();

private slots:
	void on_Open_triggered();

private:
	Ui::inio_desktopClass ui;
	Inio img;
	QImage qimg;

	void actionsEnabled();
	void reload();
	void displayImage();
};