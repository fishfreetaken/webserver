#include "ditCapturePanel.h"
#include "viewFrame.h"
#include "ditProcessPanel.h"

#include "../netconnectstatic/generalOutput.h"	//集中到这个版本中去了；

using namespace pcl;
ditCapturePanel::ditCapturePanel(QWidget *parent)
{
	//setFont(QFont("Microsoft Yahei", 11));
	//QWidget *lWidget = new QWidget(this);
	//lWidget->setWindowFlags(Qt::SubWindow); 
	for (int i= 0; i< 4; i++)
	{
		viewMat[i] = ditMat3b::zeros(1280, 960);
		viewWidget[i] = new imgShowWidget(this);
		viewWidget[i]->setShowMat(viewMat[i]);
	} 
	// 设置左、正、右的视图
	gridLayoutWidget_4 = new QWidget(this);
	gridLayoutWidget_4->setObjectName(QStringLiteral("gridLayoutWidget_4"));
	gridLayoutWidget_4->setGeometry(QRect(490, 0, 261, 341));
	Left_Grid = new QGridLayout(gridLayoutWidget_4);
	Left_Grid->setSpacing(6);
	Left_Grid->setContentsMargins(11, 11, 11, 11);
	Left_Grid->setObjectName(QStringLiteral("Left_Grid"));
	Left_Grid->setContentsMargins(0, 0, 0, 0);
	Left_Grid->addWidget(viewWidget[0]);

	gridLayoutWidget_2 = new QWidget(this);
	gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
	gridLayoutWidget_2->setGeometry(QRect(750, 0, 261, 341));
	Front_Grid = new QGridLayout(gridLayoutWidget_2);
	Front_Grid->setSpacing(6);
	Front_Grid->setContentsMargins(11, 11, 11, 11);
	Front_Grid->setObjectName(QStringLiteral("Front_Grid"));
	Front_Grid->setContentsMargins(0, 0, 0, 0);
	Front_Grid->addWidget(viewWidget[1]);

	gridLayoutWidget_3 = new QWidget(this);
	gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
	gridLayoutWidget_3->setGeometry(QRect(1010, 0, 261, 341));
	Right_Grid = new QGridLayout(gridLayoutWidget_3);
	Right_Grid->setSpacing(6);
	Right_Grid->setContentsMargins(11, 11, 11, 11);
	Right_Grid->setObjectName(QStringLiteral("Right_Grid"));
	Right_Grid->setContentsMargins(0, 0, 0, 0);
	Right_Grid->addWidget(viewWidget[2]);

	gridLayoutWidget_5 = new QWidget(this);
	gridLayoutWidget_5->setObjectName(QStringLiteral("gridLayoutWidget_5"));
	gridLayoutWidget_5->setGeometry(QRect(0, 0, 481, 661));
	Current_Grid = new QGridLayout(gridLayoutWidget_5);
	Current_Grid->setSpacing(6);
	Current_Grid->setContentsMargins(11, 11, 11, 11);
	Current_Grid->setObjectName(QStringLiteral("Current_Grid"));
	Current_Grid->setContentsMargins(0, 0, 0, 0);
	Current_Grid->addWidget(viewWidget[3]);

	// 采集的左、前、右、模型生成、模型离线按钮
	captureB[0] = new QPushButton(QIcon("images/left.png"),      QString::fromLocal8Bit("左侧"), this);
	captureB[1] = new QPushButton(QIcon("images/front.png"),     QString::fromLocal8Bit("正面"), this);
	captureB[2] = new QPushButton(QIcon("images/right.png"),     QString::fromLocal8Bit("右侧"), this);
	captureB[3] = new QPushButton(QIcon("images/model.png"),	 QString::fromLocal8Bit("模型生成"), this);
	captureB[4] = new QPushButton(QIcon("images/model_un.png"),	 QString::fromLocal8Bit("离线生成"), this);
	captureB[0]->setObjectName("leftB");

	captureB[0]->setGeometry(QRect(530, 585, 101, 51));
	captureB[0]->setIconSize(QSize(40, 40));
	captureB[0]->setCheckable(false);
	captureB[0]->setFlat(true);

	captureB[1]->setGeometry(QRect(630, 585, 101, 51));
	captureB[1]->setIconSize(QSize(40, 40));
	captureB[1]->setFlat(true);
	
	captureB[2]->setGeometry(QRect(730, 585, 101, 51));
	captureB[2]->setIconSize(QSize(40, 40));
	captureB[2]->setFlat(true);

	captureB[3]->setGeometry(QRect(855, 590, 131, 41));
	captureB[3]->setIconSize(QSize(40, 40));
	captureB[3]->setFlat(true);

	captureB[4]->setGeometry(QRect(985, 590, 131, 41));
	captureB[4]->setIconSize(QSize(40, 40));
	captureB[4]->setFlat(true);
//	captureB[4]->setEnabled(false);
	captureB[4]->setVisible(true);

	captureB[0]->setEnabled(false);
	captureB[1]->setEnabled(false);
	captureB[2]->setEnabled(false);
	captureB[3]->setEnabled(false);

	// 设置快捷键
	captureB[0]->setShortcut(Qt::Key_Left);
	captureB[1]->setShortcut(Qt::Key_Down);
	captureB[2]->setShortcut(Qt::Key_Right);
	captureB[3]->setShortcut(Qt::Key_0);

	// 启动、模型界面、退出按钮
	Start_Button = new QPushButton(QIcon("images/scan.png"), QString::fromLocal8Bit("启动"), this);
	Start_Button->setGeometry(QRect(1100, 400, 131, 64));
	Start_Button->setIconSize(QSize(64, 64));
	Start_Button->setFlat(true);

	Exit_Button = new QPushButton(QIcon("images/exit.png"), QString::fromLocal8Bit("退出"), this);
	Exit_Button->setGeometry(QRect(1100, 500, 131, 64));
	Exit_Button->setIconSize(QSize(64, 64));
	Exit_Button->setFlat(true);
	Exit_Button->setShortcut(tr("Ctrl+Q"));

	Process_Button = new QPushButton(QIcon("images/Process_model.png"), QString::fromLocal8Bit("模型查看"), this);
	Process_Button->setObjectName(QStringLiteral("Process_Button"));
	Process_Button->setGeometry(QRect(1110, 590, 131, 41));
	Process_Button->setIconSize(QSize(40, 40));
	Process_Button->setFlat(true);

	// 左、前、右、模型生成、离线生成按钮的信号和槽
	connect(captureB[0],    SIGNAL(pressed()), this,   SLOT(capture0View()));
	connect(captureB[1],    SIGNAL(pressed()), this,   SLOT(capture1View()));
	connect(captureB[2],    SIGNAL(pressed()), this,   SLOT(capture2View()));
	connect(captureB[3],    SIGNAL(pressed()), this,   SLOT(calcPointCloud()));
	connect(captureB[4],    SIGNAL(pressed()), this,   SLOT(calcPointCloudOffline()));
	connect(Start_Button,   SIGNAL(pressed()), parent, SLOT(StartCamera()));
//	connect(Process_Button, SIGNAL(pressed()), parent, SLOT(StartCamera()));
	connect(Process_Button, SIGNAL(pressed()), parent, SLOT(enter_Process()));
	connect(Exit_Button,    SIGNAL(pressed()), parent, SLOT(close()));


	// 状态信息文本框
	status_text = new QTextBrowser(this);
	status_text->setObjectName(QStringLiteral("status_text"));
	status_text->setGeometry(QRect(490, 360, 521, 220));
    status_str =  QString::fromLocal8Bit("快捷键： \n");
	status_str += QString::fromLocal8Bit("左侧面   - 左键\n");
	status_str += QString::fromLocal8Bit("正面     - 下键\n");
	status_str += QString::fromLocal8Bit("右侧面   - 右键\n");
	status_str += QString::fromLocal8Bit("模型生成 - 0键\n");
	status_str += QString::fromLocal8Bit("重置脸部特征 - R键\n");
	status_str += QString::fromLocal8Bit("------------------------------------------\n");
	status_str += QString::fromLocal8Bit("状态信息：\n");
	status_text->setText(status_str);
	
	// 相机控制判断
	pCapCtrl = new ditCaptureControl(this);
	int tFlag = pCapCtrl->init(3, viewMat);
	if ((tFlag & 0x01) == 1 || (tFlag & 0x02) == 2)
	{
		QMessageBox::critical(NULL, "", QString::fromLocal8Bit("请确认相机控制盒已连接电脑"));
	}
	//else
	//	emit 
	//else 
		//pRestruct = new ditOnlineStruct(this);
	
	bCaptured[0] = bCaptured[1] = bCaptured[2] = false;
	poffLineStruct = new ditResconstruct(this);
	connect(poffLineStruct, SIGNAL(signalUpdateStatus(QString)), this, SLOT(slotUpdateStatus(QString)));
	pMainFrm  = (viewFrame *)parent;

	//cv::Mat3b mat0 = cv::imread("c:/color0.bmp", CV_LOAD_IMAGE_COLOR);
	//cv::Mat3b mat1 = cv::imread("c:/color1.bmp", CV_LOAD_IMAGE_COLOR);
	//cv::Mat3b mat2 = cv::imread("c:/color2.bmp", CV_LOAD_IMAGE_COLOR);
	//cv::Mat3b mat3 = cv::imread("c:/color2.bmp", CV_LOAD_IMAGE_COLOR);
	//viewWidget[0]->setShowMat(mat0);
	//viewWidget[1]->setShowMat(mat1);
	//viewWidget[2]->setShowMat(mat2);
	//viewWidget[3]->setShowMat(mat3);

	cv::Mat3b mat0 = cv::imread("images/person.png", CV_LOAD_IMAGE_COLOR);
	cv::Mat3b mat1 = cv::imread("images/person.png", CV_LOAD_IMAGE_COLOR);
	cv::Mat3b mat2 = cv::imread("images/person.png", CV_LOAD_IMAGE_COLOR);
	//cv::Mat3b mat3 = cv::imread("images/camera.png", CV_LOAD_IMAGE_COLOR);
	viewWidget[0]->setShowMat(mat0);
	viewWidget[1]->setShowMat(mat1);
	viewWidget[2]->setShowMat(mat2);
	//viewWidget[3]->setShowMat(mat3);
//	imgShowWidget *viewWidget[4];   //左视图

}

ditCapturePanel::~ditCapturePanel()
{
}
void ditCapturePanel::slotUpdateStatus(QString newInfo)
{
	status_str += newInfo + "\n";
	status_text->setText(status_str);

}

void ditCapturePanel::slotUpdate3DViewer()
{
	pMainFrm->tabWidget->setCurrentIndex(1);

	char tmpBuf[50];
	pclViewer->removeShape("0");

	pPanel->outCloud = pCapCtrl->pRestruct->Getcloud();
	pCapCtrl->pRestruct->GetFacePt(pPanel->outFace3dPt);
	pPanel->outMesh  = pCapCtrl->pRestruct->GetMesh();

	pclViewer->addPointCloud<pcl::PointXYZRGB>(pPanel->outCloud, "0");

	//pclViewer->setCameraPosition(0, 0, 0, 0, 0, 1);
	//pCapCtrl->pRestruct->GetFacePt(face3dPt);
	//for (unsigned int i = 0; i < 20; i++)
	//{
	//	sprintf(tmpBuf, "sphere%i", i);
	//	pclViewer->removeShape(tmpBuf);
	//}	
	//for (unsigned int i = 0; i < face3dPt.size() - 2; i++)
	//{
	//	sprintf(tmpBuf, "sphere%i", i);
	//	pclViewer->addSphere(PointT(face3dPt[i][0], face3dPt[i][1], face3dPt[i][2]), 0.001, 255, 0, 0, tmpBuf);
	//}

#ifdef NETCOMMUNICATE
	//这个我自己添加输出pcd文件
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr ttr = pCapCtrl->pRestruct->Getcloud();

	pcl::PointCloud<pcl::PointXYZRGB>  cloudrbg;
	pcl::PointCloud<pcl::PointXYZRGB>  cloudrbg_transform;

	for (int i = 0; i<ttr->size(); i++)
	{
		pcl::PointXYZRGB ps = ttr->at(i);
		pcl::PointXYZRGB psgo;
		psgo.x = ps.x;
		psgo.y = ps.y;
		psgo.z = ps.z;
		psgo.r = ps.b;
		psgo.g = ps.g;
		psgo.b = ps.r;

		cloudrbg.push_back(psgo);
	}

	//旋转180度
	Eigen::Matrix4f transform_1 = Eigen::Matrix4f::Identity();
	float theta = M_PI; // The angle of rotation in radians  180
	transform_1(0, 0) = cos(theta);
	transform_1(0, 1) = -sin(theta);
	transform_1(1, 0) = sin(theta);
	transform_1(1, 1) = cos(theta);

	pcl::transformPointCloud(cloudrbg, cloudrbg_transform, transform_1);

	std::string filename = gSetting.nameText + '_' + gSetting.numberText + '_' + gSetting.genderText + ".pcd";

	pcl::io::savePCDFileBinary(filename, cloudrbg_transform);

	std::string personals[3] = { gSetting.nameText ,gSetting.numberText ,gSetting.genderText }; //配置文件名；
	generalOutput ims;
	pPanel->m_sql_faceid_index = ims.uploadfile(filename, personals);//upload file

#endif // NETCOMMUNICATE
}

void ditCapturePanel::slotUpdate3DVieweroffLine()
{
	pMainFrm->tabWidget->setCurrentIndex(1);

	char tmpBuf[50];
	std::vector<ditVec3d> face3dPt;
	pclViewer->removeShape("0");

	pPanel->outCloud = poffLineStruct->Getcloud();
	poffLineStruct->GetFacePt(pPanel->outFace3dPt);
	pPanel->outMesh  = poffLineStruct->GetMesh();
	
#ifdef NETCOMMUNICATE
	//这个我自己添加输出pcd文件
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr ttr = poffLineStruct->Getcloud();

	pcl::PointCloud<pcl::PointXYZRGB>  cloudrbg;
	pcl::PointCloud<pcl::PointXYZRGB>  cloudrbg_transform;

	for (int i = 0; i<ttr->size(); i++)
	{
		pcl::PointXYZRGB ps = ttr->at(i);
		pcl::PointXYZRGB psgo;
		psgo.x = ps.x;
		psgo.y = ps.y;
		psgo.z = ps.z;
		psgo.r = ps.b;
		psgo.g = ps.g;
		psgo.b = ps.r;

		//cloudrbg.push_back(ttr->at(i));
		cloudrbg.push_back(psgo);
	}

	//旋转180度
	Eigen::Matrix4f transform_1 = Eigen::Matrix4f::Identity();
	float theta = M_PI; // The angle of rotation in radians  180
	transform_1(0, 0) = cos(theta);
	transform_1(0, 1) = -sin(theta);
	transform_1(1, 0) = sin(theta);
	transform_1(1, 1) = cos(theta);

	pcl::transformPointCloud(cloudrbg, cloudrbg_transform, transform_1);

	std::string filename = gSetting.nameText + '_' + gSetting.numberText + '_' + gSetting.genderText + ".pcd";
	pcl::io::savePCDFileBinary(filename, cloudrbg_transform);

	std::string personals[3] = { gSetting.nameText ,gSetting.numberText ,gSetting.genderText }; //配置文件名；
	generalOutput ims;
	pPanel->m_sql_faceid_index = ims.uploadfile(filename, personals);//upload file

#endif // NETCOMMUNICATE

	pclViewer->addPointCloud<pcl::PointXYZRGB>(pPanel->outCloud, "0");
	//pclViewer->addSphere(ditPointT(0, 0, 0), 0.001, 255, 255, 0, "sourcepoint");

	//pcl::io::savePCDFileASCII("zhouface.pcd", cloudrbg);

	/*pPanel->outCloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
	
	pcl::io::loadPCDFile<pcl::PointXYZRGB>("zhouface.pcd", *pPanel->outCloud);

	pclViewer->addPointCloud<pcl::PointXYZRGB>(pPanel->outCloud, "0");*/

	//pcl::io::savePLYFileBinary

	//pcl::io::saveOBJFile("zhouface.pcl",cloudrbg);

//	pclViewer->addPolygonMesh(*pPanel->outMesh, "1");
}

void ditCapturePanel::capture0View()
{
	bCaptured[0] = true;
	if (bCaptured[0] && bCaptured[1] && bCaptured[2])
		captureB[3]->setEnabled(true);
	emit signalCaptureView(0);
}

void ditCapturePanel::capture1View()
{
	bCaptured[1] = true;
	if (bCaptured[0] && bCaptured[1] && bCaptured[2])
		captureB[3]->setEnabled(true);
	emit signalCaptureView(1);
}

void ditCapturePanel::capture2View()
{
	bCaptured[2] = true;
	if (bCaptured[0] && bCaptured[1] && bCaptured[2])
		captureB[3]->setEnabled(true);
	emit signalCaptureView(2);
}

void ditCapturePanel::calcPointCloudOffline()
{
	emit signalCalcPtCloud();
}

void ditCapturePanel::calcPointCloud()
{
	captureB[3]->setEnabled(false);
	emit signalCaptureView(3);
}

void ditCapturePanel::slotUpdatePreview(int No)
{
	if (No>= 0 || No <= 3)
		viewWidget[No]->setShowMat(viewMat[No]);
}

void ditCapturePanel::slotUpdateButton(bool enabled)
{
	captureB[0]->setEnabled(enabled);
	captureB[1]->setEnabled(enabled);
	captureB[2]->setEnabled(enabled);
}

void ditCapturePanel::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_R)
		emit signalCaptureView(4);

	//if (event->key() == Qt::Key_Left)
	//	capture0View();
	//if (event->key() == Qt::Key_Down)
	//	capture1View();
	//if (event->key() == Qt::Key_Right)
	//	capture0View(); 
}
