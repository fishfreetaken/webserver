#pragma once
#include "ditHeadScanner_global.h"
#include <string>
class viewFrame;
class ditResconstruct;
class ditProcessPanel;
class ditCapturePanel : public QWidget
{
	Q_OBJECT
public:
	ditCapturePanel(QWidget *parent);
	~ditCapturePanel();

public:
	imgShowWidget *viewWidget[4];   //◊Û ”Õº
	ditMat3b       viewMat[4];

	QWidget *gridLayoutWidget_2;
	QGridLayout *Front_Grid;
	QWidget *gridLayoutWidget_3;
	QGridLayout *Right_Grid;
	QWidget *gridLayoutWidget_4;
	QGridLayout *Left_Grid;
	QWidget *gridLayoutWidget_5;
	QGridLayout *Current_Grid;

	QPushButton *Start_Button;
	QPushButton *Save_Button;
	QPushButton *Exit_Button;
	QPushButton *Process_Button;

	QTextBrowser *status_text;
signals:
	void signalCaptureView(int);
	void signalCalcPtCloud();
	
public slots:
	void calcPointCloudOffline();
	void slotUpdatePreview(int No);
	void slotUpdateButton(bool);
	void slotUpdate3DViewer();
	void slotUpdate3DVieweroffLine();
	void slotUpdateStatus(QString);

	void keyPressEvent(QKeyEvent *event);
	void capture0View();
	void capture1View();
	void capture2View();
	void calcPointCloud();
public:
	ditCaptureControl *pCapCtrl;  
	viewFrame         *pMainFrm;
	ditProcessPanel   *pPanel;
	ditResconstruct   *poffLineStruct;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> pclViewer;
private:
	bool bAuthorized;
	QPushButton *captureB[5];
	bool bCaptured[3];
	QString status_str;
};
