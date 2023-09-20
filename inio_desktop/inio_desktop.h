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
	void on_Save_triggered();
	void on_SaveAs_triggered();
	void on_Undo_triggered();
	void on_Redo_triggered();
	void on_BoxFilter_triggered();
	void on_BFExe_clicked();
	void on_GaussianFilter_triggered();
	void on_GFExe_clicked();
	//void on_ContrastEmphasize_triggered();
	//void on_EquHist_triggered();
	//void on_GammaCorrection_triggered();
	//void on_Posterize_triggered();
	//void on_Laplacian_triggered();
	//void on_Prewitt_triggered();
	//void on_Sobel_triggered();
	//void on_LapUsm_triggered();
	//void on_MeanUsm_triggered();

private:
	Ui::inio_desktopClass ui;
	Inio img;
	Inio preview;
	QPixmap _pixmap;

	void actionsEnabled();
	void reload();

protected:
	void resizeEvent(QResizeEvent* event);
};