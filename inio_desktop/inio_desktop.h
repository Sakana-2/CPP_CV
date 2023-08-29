#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_inio_desktop.h"

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
};
