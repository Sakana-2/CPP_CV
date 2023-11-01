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
	void on_Reset_triggered();
	void on_AdaptiveThreshold_triggered();
	void on_ATExe_clicked();
	void on_BoxFilter_triggered();
	void on_BFExe_clicked();
	void on_GaussianFilter_triggered();
	void on_GFExe_clicked();
	void on_Posterize_triggered();
	void on_PosterizeExe_clicked();
	void on_ContrastEmphasize_triggered();
	void on_CEExe_clicked();
	void on_EquHist_triggered();
	void on_EHExe_clicked();
	void on_GammaCorrection_triggered();
	void on_GCExe_clicked();
	void on_Invert_triggered();
	void on_INExe_clicked();
	void on_Laplacian_triggered();
	void on_LPExe_clicked();
	void on_Prewitt_triggered();
	void on_PRExe_clicked();
	void on_Sobel_triggered();
	void on_SBExe_clicked();
	void on_Threshold_triggered();
	void on_THExe_clicked();
	void on_MeanUsm_triggered();
	void on_MUExe_clicked();
	void on_LaplUsm_triggered();
	void on_LUExe_clicked();
	void on_BDither_triggered();
	void on_BDExe_clicked();

private:
	Ui::inio_desktopClass ui;
	Inio img;
	Inio preview;
	QPixmap _pixmap;
	std::vector<QGroupBox*> displayedBox = {};

	void actionsEnabled();
	void PropBoxIncubator();
	void reload();

protected:
	void resizeEvent(QResizeEvent* event);
};