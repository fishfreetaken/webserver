#include "ditProcessPanel.h"
#include <QtWidgets>
#include "QDebug"
#include "imgShowWidget.h"
#include "vtkRenderWindow.h"
#include "QVTKWidget.h"
#include "InfoDlg.h"
#include <QLabel>
#include <QMovie>
//#include "../ditHeadModel/ditResconstruct.h"
#include "ditCapturePanel.h"
//#pragma execution_character_set("utf-8")

//#include "../ditParmExtLib/ditHeadParmExt.h"
//#include "../ditParmExtLib/ditFootParmExt.h"

//#include "../netconnectstatic/httpconnect.h" //之前一个版本用的
#include "../netconnectstatic/generalOutput.h"	//集中到这个版本中去了；

ditProcessPanel::ditProcessPanel(QWidget *parent)
{

	//setFont(QFont("Microsoft Yahei", 11));
	pclViewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));

	QVTKWidget *qvtkWidget = new QVTKWidget(this);
	//qvtkWidget->resize(this->geometry().width(), this->geometry().height());
	qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
	qvtkWidget->SetRenderWindow(pclViewer->getRenderWindow());
	pclViewer->setupInteractor(qvtkWidget->GetInteractor(), qvtkWidget->GetRenderWindow());
	pclViewer->registerKeyboardCallback(&keyboardEvent, this);	// 显示
	pclViewer->registerMouseCallback(&mousedEvent, this);
	pclViewer->registerPointPickingCallback(&pickCallEvent, this);
	pclViewer->initCameraParameters();


	// 设置GIF和QVTKWidget
	QLabel *gif_label = new QLabel();
	QMovie *movie = new QMovie("images/model_img.gif");
	gif_label->setFixedSize(271, 271);
	QWidget *gif_gridLayoutWidget = new QWidget(this);
	gif_gridLayoutWidget->setGeometry(QRect(980, 10, 271, 271));
	QGridLayout *gif_Grid = new QGridLayout(gif_gridLayoutWidget);
	gif_Grid->setSpacing(6);
	gif_Grid->setContentsMargins(11, 11, 11, 11);
	gif_Grid->setContentsMargins(0, 0, 0, 0);
	gif_Grid->addWidget(gif_label);
	gif_label->setMovie(movie);
	movie->start();

	QLabel *gif_label2 = new QLabel();
	QMovie *movie2 = new QMovie("images/Process_gif.gif");
	gif_label2->setFixedSize(250, 250);
	QWidget *gif_gridLayoutWidget2 = new QWidget(this);
	gif_gridLayoutWidget2->setGeometry(QRect(990, 230, 250, 250));
	QGridLayout *gif_Grid2 = new QGridLayout(gif_gridLayoutWidget2);
	gif_Grid2->setSpacing(6);
	gif_Grid2->setContentsMargins(11, 11, 11, 11);
	gif_Grid2->setContentsMargins(0, 0, 0, 0);
	gif_Grid2->addWidget(gif_label2);
	gif_label2->setMovie(movie2);
	movie2->start();

	gridLayoutWidget = new QWidget(this);
	gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
	gridLayoutWidget->setGeometry(QRect(0, 0, 961, 646));
	Process_Grid = new QGridLayout(gridLayoutWidget);
	Process_Grid->setSpacing(6);
	Process_Grid->setContentsMargins(11, 11, 11, 11);
	Process_Grid->setObjectName(QStringLiteral("Process_Grid"));
	Process_Grid->setContentsMargins(0, 0, 0, 0);
	Process_Grid->setGeometry(QRect(0, 0, 961, 646));

	// 返回和保存按钮
	Return_Button = new QPushButton(QIcon("images/Return_Home.png"), QString::fromLocal8Bit("扫描界面"), this);
	Return_Button->setObjectName(QStringLiteral("Return_Button"));
	Return_Button->setGeometry(QRect(1110, 590, 131, 41));
	Return_Button->setIconSize(QSize(40, 40));
	Return_Button->setFlat(false);
	Return_Button->setFlat(true);

	Save_Button = new QPushButton(QIcon("images/extract.png"), QString::fromLocal8Bit("参数提取"), this);
	Save_Button->setObjectName(QStringLiteral("Save_Button"));
	Save_Button->setGeometry(QRect(1000, 590, 91, 41));
	Save_Button->setIconSize(QSize(40, 40));
	Save_Button->setFlat(false);
	Save_Button->setFlat(true);

	connect(Save_Button, &QPushButton::pressed, this, &ditProcessPanel::extractParametaers);

	Process_Grid->addWidget(qvtkWidget);

	pclViewer->setCameraPosition(0, 0, 0, -1, 0, 0);
	//while (!pclViewer->wasStopped())
	//{
	//	pclViewer->spinOnce(100);
	//	boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	//}
}
void ditProcessPanel::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}
void ditProcessPanel::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;
}


void ditProcessPanel::createActions()
{
	//QAction *scanAct = new QAction(QIcon("images/scan.png"), QString::fromLocal8Bit("一键"), this);
	//scanAct->setToolTip(QString::fromLocal8Bit("一键启动"));
	//scanAct->setShortcut(tr("Ctrl+S"));
	////connect(scanAct, &QAction::triggered, this, &ditProcessPanel::StartScan);
	////connect(scanAct, &QAction::triggered, this, &ditProcessPanel::super4PCS);
	//QAction *capAct = new QAction(QIcon("images/capture.png"), QString::fromLocal8Bit("采集"), this);
	//capAct->setToolTip(QString::fromLocal8Bit("采集图像"));
	////connect(capAct, &QAction::triggered, this, &ditProcessPanel::CaptureImg);
	////capAct->setShortcut(tr("Ctrl+C"));
	//QAction *conAct = new QAction(QIcon("images/construct.png"), QString::fromLocal8Bit("建模"), this);
	//conAct->setToolTip(QString::fromLocal8Bit("重建模型"));
	////connect(conAct, &QAction::triggered, this, &ditProcessPanel::ConstructModel);
	////conAct->setShortcut(tr("Ctrl+R"));

	//QAction *extAct = new QAction(QIcon("images/extract.png"), QString::fromLocal8Bit("提取"), this);
	//extAct->setToolTip(QString::fromLocal8Bit("脚型参数"));
	////connect(extAct, &QAction::triggered, this, &ditProcessPanel::Extract);
	////extAct->setShortcut(tr("Ctrl+E"));

	//QAction *openAct = new QAction(QIcon("images/open.png"), QString::fromLocal8Bit("打开"), this);
	//openAct->setToolTip(QString::fromLocal8Bit("打开点云"));
	////openAct->setShortcut(tr("Ctrl+O"));
	////connect(openAct, &QAction::triggered, this, &ditProcessPanel::openCloud);

	//QAction *faceMarkerAct = new QAction(QIcon("images/faceMarker.png"), QString::fromLocal8Bit("人脸"), this);
	//faceMarkerAct->setToolTip(QString::fromLocal8Bit("人脸标注"));
	////connect(faceMarkerAct, &QAction::triggered, this, &ditProcessPanel::FaceMarker);

	//QAction *showAct = new QAction(QIcon("images/paste.png"), QString::fromLocal8Bit("泊松"), this);
	//showAct->setToolTip(QString::fromLocal8Bit("泊松重建"));
	////connect(showAct, &QAction::triggered, this, &ditProcessPanel::showPoint);
	////connect(showAct, &QAction::triggered, this, &ditProcessPanel::OneShot);

	//QAction *icpAct = new QAction(QIcon("images/register.png"), QString::fromLocal8Bit("配准"), this);
	//icpAct->setToolTip(QString::fromLocal8Bit("ICP点云配准"));
	////connect(icpAct, &QAction::triggered, this, &ditProcessPanel::icpTest);
	////connect(icpAct, &QAction::triggered, this, &ditProcessPanel::super4PCS);

	//QAction *exitAct = new QAction(QIcon("images/exit.png"), QString::fromLocal8Bit("退出"), this);
	//exitAct->setShortcut(tr("Ctrl+Q"));
	////connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

}


void ditProcessPanel::readSettings()
{
	//QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	//const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
	//if (geometry.isEmpty())
	//{
	//	const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
	//	resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
	//	move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
	//}
	//else 
	//{
	//	restoreGeometry(geometry);
	//}
	//QString fileName = settings.value("outFile", QByteArray()).toString();

}

void ditProcessPanel::writeSettings()
{
	//QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	//settings.setValue("geometry", saveGeometry());
	//settings.setValue("outFile", QString::fromLocal8Bit("d:/temp"));
	//QString t1 = QCoreApplication::organizationName();
	//QString t2 = QCoreApplication::applicationName();

	//QSettings settings("footScanner.ini", QSettings::IniFormat); // 当前目录的INI文件
	//settings.beginGroup("Camera");
	//settings.setValue("ComPort", "COM3");
	//settings.setValue("WorkDir", "D:/temp");
	//settings.endGroup();

}

void ditProcessPanel::openCloud()
{
	QStringList fileNames = QFileDialog::getOpenFileNames();
	if (fileNames.size() < 2)
		return;

}
void ditProcessPanel::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_S)
		int x = 0;

	//if (event->key() == Qt::Key_Left)
	//	capture0View();
	//if (event->key() == Qt::Key_Down)
	//	capture1View();
	//if (event->key() == Qt::Key_Right)
	//	capture0View(); 
}


void ditProcessPanel::addPoint(ditPointT x)
{
	if (face3dPt_pick.size() >= 2)
	{
		pclViewer->removeAllShapes();

		face3dPt_pick.clear();
		//return;
	}
	else if (face3dPt_pick.size()==0)
	{
		pclViewer->removeAllShapes();
	}

	ditVec3d p(x.x, x.y, x.z);
	face3dPt_pick.push_back(p);//先左后右，后期可以自动识别分类；
	char gw = 65;
	gw = gw + face3dPt_pick.size();
	std::string ag = "pickpoint";
	ag += gw;

	pclViewer->addSphere(m_picked_point, 0.001, 255, 0, 0, ag);
}

void ditProcessPanel::extractParametaers()//主函数调用入口；
{

	//ditMesh * pMesh = new ditMesh();
	//OpenMesh::IO::read_mesh(*pMesh, "d:/cd1L.ply");
	//OpenMesh2pclMesh((void*)pMesh, xxMesh);
	//pcl::PolygonMesh tMesh;
	////pcl::PointCloud<pcl::PointXYZ>::Ptr xxCloud(new pcl::PointCloud<pcl::PointXYZ>);
	//pcl::io::loadPLYFile("d:/xx.ply", tMesh);
	//pclViewer->addPolygonMesh(tMesh);

	//return;

	//pcl::io::savePLYFile("d:/xx.ply", *outCloud);
	if (face3dPt_pick.size() < 2)
	{
		QMessageBox::critical(NULL, "", QString::fromLocal8Bit("请拾取最高挂耳点"));
		return;
	}

	//face3dPt.clear();

	////poffLineStruct = poff;
	////poffLineStruct->GetFacePt(face3dPt);		//13个点
	//for (auto i : caputreControl->_face3dPt)//13 online  or offline;
	//{
	//	face3dPt.push_back(i);
	//}

	std::vector<ditVec3d>  outFace3dPt_temp;
	for (auto i: outFace3dPt)
	{
		outFace3dPt_temp.push_back(i);
	}

	//for (auto i : face3dPt_pick)
	//{
	//	outFace3dPt_temp.push_back(i); //for two points
	//}
	outFace3dPt_temp.push_back(face3dPt_pick[0]);
	outFace3dPt_temp.push_back(face3dPt_pick[1]);

	//face3dPt_pick.clear();

	//pclViewer->removeShape("pickpoint1");
	//pclViewer->removeShape("pickpoint2");

	if (outFace3dPt_temp.size() == 14)
		PickoutFourParameter(outFace3dPt_temp);
	else 
		QMessageBox::critical(NULL, "", QString::fromLocal8Bit("请输入左右两边最高挂耳点"));

	face3dPt_pick.clear();
	return;
}

void ditProcessPanel::PushSinglePoint(ditVec3d p, std::vector<std::vector<double>> &arr)
{
	Eigen::Matrix4d transform_1 = Eigen::Matrix4d::Identity();
	float theta = M_PI; // The angle of rotation in radians  180
	transform_1(0, 0) = cos(theta);
	transform_1(0, 1) = -sin(theta);
	transform_1(1, 0) = sin(theta);
	transform_1(1, 1) = cos(theta);

	//Eigen::Affine3d ag;
	//ag = transform_1;

	//Matrix4f transform;
	Eigen::Transform<double, 3, Eigen::Affine> t_src2w(transform_1);


	Eigen::Vector3d tf(p[0], p[1], p[2]), atf;
	pcl::transformPoint(tf, atf, t_src2w);

	std::vector<double> arrs;
	/*arrs.push_back(p[0]);
	arrs.push_back(p[1]);
	arrs.push_back(p[2]);*/

	arrs.push_back(atf[0]);
	arrs.push_back(atf[1]);
	arrs.push_back(atf[2]);

	arr.push_back(arrs);
}

void  ditProcessPanel::PickoutFourParameter(std::vector<ditVec3d>& outFace3dPt_temp)
{
	//std::string personname = gSetting.nameText;
	//std::string personphone = gSetting.numberText;
	//bool personsex = gSetting.genderID;

	//std::string personsex = gSetting.genderText;//美女 帅哥

	/*if (m_mutex_pick) {
		printf("another invoking!return!");
		return;
	}*/

	std::string personals[3] = { gSetting.nameText ,gSetting.numberText ,"1" }; //配置文件名；


	std::vector<std::vector<double>> httpdouble;
	std::vector<std::vector<int>>	httpline;

	std::vector<std::string> httplinestr;


	char tmpBuf[50];
	std::string tmpBufstring;

	/*
		瞳距
	*/
	parameter_[0] = cv::norm(outFace3dPt_temp[4] - outFace3dPt_temp[5]);
	printf("瞳孔中心距：%f\n", parameter_[0]);

	sprintf(tmpBuf, "Centre of two eye's pupils: %.2f cm\n", parameter_[0] * 100);
	tmpBufstring = tmpBuf;
	pclViewer->addText(tmpBufstring, 10, 600, 1.0, 0.0, 0.0, "TextParameter0"); //在坐标系上添加
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();

	sprintf(tmpBuf, "%.2f cm\n", parameter_[0] * 100);
	tmpBufstring = tmpBuf;
	ditVec3d eye_text_point = outFace3dPt_temp[4] + (outFace3dPt_temp[5] - outFace3dPt_temp[4]) / 2;
	pclViewer->addText3D(tmpBufstring, ditPointT(eye_text_point[0], eye_text_point[1], eye_text_point[2] - 0.02), 0.007, 1, 0, 0, "text_eye_widestLine");
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();

	pclViewer->addLine(ditPointT(outFace3dPt_temp[4][0], outFace3dPt_temp[4][1], outFace3dPt_temp[4][2] - 0.02), ditPointT(outFace3dPt_temp[5][0], outFace3dPt_temp[5][1], outFace3dPt_temp[5][2] - 0.02), 1.0, 0.0, 0.0, "eyebolicline1");
	pclViewer->addLine(ditPointT(outFace3dPt_temp[4][0], outFace3dPt_temp[4][1], outFace3dPt_temp[4][2]),        ditPointT(outFace3dPt_temp[4][0], outFace3dPt_temp[4][1], outFace3dPt_temp[4][2] - 0.02), 1.0, 0.0, 0.0, "eyebolicline2");
	pclViewer->addLine(ditPointT(outFace3dPt_temp[5][0], outFace3dPt_temp[5][1], outFace3dPt_temp[5][2]),        ditPointT(outFace3dPt_temp[5][0], outFace3dPt_temp[5][1], outFace3dPt_temp[5][2] - 0.02), 1.0, 0.0, 0.0, "eyebolicline3");

	PushSinglePoint(outFace3dPt_temp[4], httpdouble);
	PushSinglePoint(outFace3dPt_temp[5], httpdouble);
	PushSinglePoint(ditVec3d(outFace3dPt_temp[4][0], outFace3dPt_temp[4][1], outFace3dPt_temp[4][2] - 0.02), httpdouble);
	PushSinglePoint(ditVec3d(outFace3dPt_temp[5][0], outFace3dPt_temp[5][1], outFace3dPt_temp[5][2] - 0.02), httpdouble);

	httplinestr.push_back("0-2-3-1");
	
	/*
		头部最宽的距离
	*/

	ditVec3d head_middle_surface_coe;//头部平面：垂直于面部，由4 5 垂直直线过中电的平面；
	ditVec3d line_end_coe;
	ditVec3d eye_point_mid;
	//eye_point_mid = (face3dPt[4] + face3dPt[5]) / 2;
	//line_end_coe = (face3dPt[12] - face3dPt[13]);

	line_end_coe = outFace3dPt_temp[4] - outFace3dPt_temp[5];
	eye_point_mid = (outFace3dPt_temp[4] + outFace3dPt_temp[5]) / 2;

	head_middle_surface_coe = (outFace3dPt_temp[4] - outFace3dPt_temp[5]); //平面用来判断左右两个点；

	double head_middle_surface_d;
	head_middle_surface_d = 0 - head_middle_surface_coe.dot((outFace3dPt_temp[4] + outFace3dPt_temp[5]) / 2);

	//ditVec3d point_face_surface_mid;
	//point_face_surface_mid = surfaceLineCrossPoint(line_end_coe, face3dPt[12], head_middle_surface_coe, eye_point_mid);


	//直线line_end_coe上的 point_face_surface_mid 点沿着 face_surface_coe 方向走；
	//pcl::PolygonMesh::Ptr ptrpclpolymesh = caputreControl->reconstructCloud;//poffLineStruct->GetMesh();
	ditMesh mesh;

	pclMesh2OpemMesh(outMesh, (void*)(&mesh));

	//std::string plyfile = personname + ".ply"; //输出plymesh文件用于压缩； 
	//OpenMesh::IO::write_mesh(mesh, plyfile, 1);

	int step = 200;//步长

	ditVec3d stepnormal = ((outFace3dPt_temp[12] + outFace3dPt_temp[13]) / 2 - (outFace3dPt_temp[4] + outFace3dPt_temp[5]) / 2) / step;

	ditVec3d leftwidestpoint;
	ditVec3d rightwidestpoint;
	double widestLength = 0;
	double dtemp;
	ditVec3d line_move_point = eye_point_mid;
	for (int i = 1; i < step*0.6; i++)
	{
		ditVec3d leftpointtemp;
		ditVec3d rightpointtemp;
		line_move_point += stepnormal;
		dtemp = wideLineTwoPoint(leftpointtemp, rightpointtemp, outFace3dPt_temp[4], line_end_coe, line_move_point, mesh, head_middle_surface_coe, head_middle_surface_d);
		if (dtemp > widestLength)
		{
			widestLength = dtemp;
			leftwidestpoint = leftpointtemp;
			rightwidestpoint = rightpointtemp;
		}
	}
	parameter_[1] = widestLength;//头部最宽的距离；
	pclViewer->addSphere(ditPointT(leftwidestpoint[0], leftwidestpoint[1], leftwidestpoint[2]), 0.001, 1, 0, 0, "sphere12");
	pclViewer->addSphere(ditPointT(rightwidestpoint[0], rightwidestpoint[1], rightwidestpoint[2]), 0.001, 1, 0, 0, "sphere13");
	printf("头两侧最宽距离：%f\n", parameter_[1]);

	pclViewer->addLine(ditPointT(rightwidestpoint[0] - 0.1, rightwidestpoint[1], rightwidestpoint[2]), ditPointT(leftwidestpoint[0] - 0.1, leftwidestpoint[1], leftwidestpoint[2]), 1.0, 0.0, 0.0, "widestline1");
	pclViewer->addLine(ditPointT(leftwidestpoint[0], leftwidestpoint[1], leftwidestpoint[2]), ditPointT(leftwidestpoint[0] - 0.1, leftwidestpoint[1], leftwidestpoint[2]), 1.0, 0.0, 0.0, "widestline2");
	pclViewer->addLine(ditPointT(rightwidestpoint[0] - 0.1, rightwidestpoint[1], rightwidestpoint[2]), ditPointT(rightwidestpoint[0], rightwidestpoint[1], rightwidestpoint[2]), 1.0, 0.0, 0.0, "widestline3");

	PushSinglePoint(leftwidestpoint, httpdouble);//4
	PushSinglePoint(rightwidestpoint, httpdouble);//5
	PushSinglePoint(ditVec3d(rightwidestpoint[0] - 0.1, rightwidestpoint[1], rightwidestpoint[2]), httpdouble);//6
	PushSinglePoint(ditVec3d(leftwidestpoint[0] - 0.1, leftwidestpoint[1], leftwidestpoint[2]), httpdouble);//7

	httplinestr.push_back("4-7-6-5");

	sprintf(tmpBuf, "Head's widest length: %.2f cm\n", parameter_[1] * 100);
	tmpBufstring = tmpBuf;
	pclViewer->addText(tmpBufstring, 10, 580, 1, 0, 0, "TextParameter1"); //在坐标系上添加
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();

	sprintf(tmpBuf, "%.2f cm\n", parameter_[1] * 100);
	tmpBufstring = tmpBuf;
	ditVec3d text_widest_point = leftwidestpoint + (rightwidestpoint - leftwidestpoint) / 2;
	pclViewer->addText3D(tmpBufstring, ditPointT(text_widest_point[0] - 0.1, text_widest_point[1], text_widest_point[2]), 0.007, 1, 0, 0, "text_widestLine");
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();

	/*
	到眼球最高点的垂直长度；
	*/
	//right：
	ditVec3d face_surface_coe;//面部平面：由点4，5，8 确定；直线平移方向；
	face_surface_coe = (outFace3dPt_temp[4] - outFace3dPt_temp[8]).cross(outFace3dPt_temp[5] - outFace3dPt_temp[8]); //法向朝向里；

	ditVec3d face_vetex_coe = (outFace3dPt_temp[4] - outFace3dPt_temp[5]);

	ditVec3d  cross_point_right = surfaceLineCrossPoint(face_vetex_coe, outFace3dPt_temp[4], face_vetex_coe, outFace3dPt_temp[13]);
	parameter_[3] = cv::norm(cross_point_right - outFace3dPt_temp[13]);

	//pclViewer->addLine(PointT(cross_point_right[0], cross_point_right[1], cross_point_right[2]), PointT(outFace3dPt[13][0], outFace3dPt[13][1], outFace3dPt[13][2]), 1.0, 0.0, 0.0, "rightvertexline");

	printf("右耳朵挂眼最高点垂直长：%f\n", parameter_[3]);

	ditVec3d  surface_cross_point_right = cross_point_right;//surfaceLineCrossPoint(outFace3dPt[13] - cross_point_right, outFace3dPt[13], face_surface_coe, outFace3dPt[8]);
	ditVec3d  surface_cross_point_vertical_right = surfaceLineCrossPoint(face_surface_coe, outFace3dPt_temp[13], face_surface_coe, outFace3dPt_temp[8]);

	double big_line_right = cv::norm(outFace3dPt_temp[13] - surface_cross_point_right);
	double cos_line_right = cv::norm(surface_cross_point_right - surface_cross_point_vertical_right);

	parameter_[5] = 180 * acos(cos_line_right / big_line_right) / (M_PI);


	//left：
	face_vetex_coe = (outFace3dPt_temp[5] - outFace3dPt_temp[4]);

	ditVec3d  cross_point_left = surfaceLineCrossPoint(face_vetex_coe, outFace3dPt_temp[5], face_vetex_coe, outFace3dPt_temp[12]);
	parameter_[2] = cv::norm(cross_point_left - outFace3dPt_temp[12]);


	printf("左耳朵挂眼最高点垂直长：%f\n", parameter_[2]);

	sprintf(tmpBuf, "Right hang point vertical length: %.2f cm\n", parameter_[3] * 100);
	tmpBufstring = tmpBuf;
	pclViewer->addText(tmpBufstring, 10, 560, 1, 0, 0, "TextParameter3"); //在坐标系上添加
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();

	sprintf(tmpBuf, "%.2f cm\n", (parameter_[3] + parameter_[2]) * 50);
	tmpBufstring = tmpBuf;
	ditVec3d right_cross_test_pos = cross_point_right + (outFace3dPt_temp[13] - cross_point_right) / 2;
	pclViewer->addText3D(tmpBufstring, ditPointT(right_cross_test_pos[0], right_cross_test_pos[1], right_cross_test_pos[2]), 0.007, 1, 0, 0, "text_right_hang_widestLine");
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();


	sprintf(tmpBuf, "Left hang point vertical length: %.2f cm\n", parameter_[2] * 100);
	tmpBufstring = tmpBuf;
	pclViewer->addText(tmpBufstring, 10, 540, 1, 0, 0, "TextParameter2"); //在坐标系上添加
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();

	sprintf(tmpBuf, "%.2f cm\n", (parameter_[3] + parameter_[2]) * 50);
	tmpBufstring = tmpBuf;
	ditVec3d left_cross_test_pos = cross_point_left + (outFace3dPt_temp[12] - cross_point_left) / 2;
	pclViewer->addText3D(tmpBufstring, ditPointT(left_cross_test_pos[0], left_cross_test_pos[1], left_cross_test_pos[2]), 0.007, 1, 0, 0, "text_left_hang_widestLine");
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();

	parameter_[2] = (parameter_[3] + parameter_[2]) * 50;
	parameter_[3] = (parameter_[3] + parameter_[2]) * 50;//这个是求一个平均；

	ditVec3d  surface_cross_point_left = cross_point_left;// surfaceLineCrossPoint(outFace3dPt[12] - cross_point_left, outFace3dPt[12], face_surface_coe, outFace3dPt[8]);//到直线的点
	ditVec3d  surface_cross_point_vertical_left = surfaceLineCrossPoint(face_surface_coe, outFace3dPt_temp[12], face_surface_coe, outFace3dPt_temp[8]);//到面的点

	double big_line_left = cv::norm(outFace3dPt_temp[12] - surface_cross_point_left);
	double cos_line_left = cv::norm(surface_cross_point_left - surface_cross_point_vertical_left);

	parameter_[4] = 180 * acos(cos_line_left / big_line_left) / (M_PI);

	parameter_[6] = (parameter_[5] + parameter_[4]) / 2;


	double aver_line = (cos_line_left + cos_line_right) / 2;
	ditVec3d aver_line_move = (surface_cross_point_left - surface_cross_point_vertical_left) + (surface_cross_point_right - surface_cross_point_vertical_right);
	
	/*
		角度线显示：
	*/

	/*ditVec3d outFace3dPt_13;
	double outFace3dPt_13_len = (tan(M_PI*parameter_[6]/180))*cv::norm(surface_cross_point_right - surface_cross_point_vertical_right);
	outFace3dPt_13 = (outFace3dPt_13_len / cv::norm(face_surface_coe))*face_surface_coe;*/
	surface_cross_point_right = surface_cross_point_vertical_right + aver_line_move*(aver_line / (cv::norm(aver_line_move)));
	pclViewer->addLine(ditPointT(surface_cross_point_right[0], surface_cross_point_right[1], surface_cross_point_right[2]), ditPointT(surface_cross_point_vertical_right[0], surface_cross_point_vertical_right[1], surface_cross_point_vertical_right[2]), 0.0, 1.0, 0.0, "rightangleline1");
	pclViewer->addLine(ditPointT(surface_cross_point_right[0], surface_cross_point_right[1], surface_cross_point_right[2]), ditPointT(outFace3dPt_temp[13][0], outFace3dPt_temp[13][1], outFace3dPt_temp[13][2]), 1.0, 0.0, 0.0, "rightangleline2");
	pclViewer->addLine(ditPointT(outFace3dPt_temp[13][0], outFace3dPt_temp[13][1], outFace3dPt_temp[13][2]), ditPointT(surface_cross_point_vertical_right[0], surface_cross_point_vertical_right[1], surface_cross_point_vertical_right[2]), 0.0, 1.0, 0.0, "rightangleline3");

	PushSinglePoint(surface_cross_point_right, httpdouble);//8
	PushSinglePoint(outFace3dPt_temp[13], httpdouble);//9
	PushSinglePoint(surface_cross_point_vertical_right, httpdouble);//10

	httplinestr.push_back("8-9-10-8");

	/*ditVec3d outFace3dPt_12;
	double outFace3dPt_12_len = (tan(M_PI*parameter_[6] / 180))*cv::norm(surface_cross_point_left - surface_cross_point_vertical_left);
	outFace3dPt_12 = (outFace3dPt_12_len / cv::norm(face_surface_coe))*face_surface_coe;*/
	surface_cross_point_left = surface_cross_point_vertical_left + aver_line_move*(aver_line / (cv::norm(aver_line_move)));
	pclViewer->addLine(ditPointT(surface_cross_point_left[0], surface_cross_point_left[1], surface_cross_point_left[2]), ditPointT(surface_cross_point_vertical_left[0], surface_cross_point_vertical_left[1], surface_cross_point_vertical_left[2]), 0.0, 1.0, 0.0, "leftangleline1");
	pclViewer->addLine(ditPointT(surface_cross_point_left[0], surface_cross_point_left[1], surface_cross_point_left[2]), ditPointT(outFace3dPt_temp[12][0], outFace3dPt_temp[12][1], outFace3dPt_temp[12][2]), 1.0, 0.0, 0.0, "leftangleline2");
	pclViewer->addLine(ditPointT(outFace3dPt_temp[12][0], outFace3dPt_temp[12][1], outFace3dPt_temp[12][2]), ditPointT(surface_cross_point_vertical_left[0], surface_cross_point_vertical_left[1], surface_cross_point_vertical_left[2]), 0.0, 1.0, 0.0, "leftangleline3");

	PushSinglePoint(surface_cross_point_left, httpdouble);//11
	PushSinglePoint(outFace3dPt_temp[12], httpdouble);//12
	PushSinglePoint(surface_cross_point_vertical_left, httpdouble);//13

	httplinestr.push_back("11-12-13-11");

	printf("左耳挂眼睛眼角角度：%f °C\n", parameter_[4]);

	printf("右耳挂眼睛眼角角度：%f °C\n", parameter_[5]);

	printf("平均挂眼睛眼角角度：%f °C\n", parameter_[6]);

	sprintf(tmpBuf, "Right and left glim hanged up angle: %f deg\n", parameter_[6]);
	tmpBufstring = tmpBuf;
	pclViewer->addText(tmpBufstring, 10, 520, 1, 0, 0, "TextParameter5"); //在坐标系上添加
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();

	sprintf(tmpBuf, "%.2f deg\n", parameter_[6]);
	tmpBufstring = tmpBuf;
	pclViewer->addText3D(tmpBufstring, ditPointT(surface_cross_point_left[0], surface_cross_point_left[1], surface_cross_point_left[2]), 0.007, 1, 0, 0, "text_left_angle_average");
	pclViewer->addText3D(tmpBufstring, ditPointT(surface_cross_point_right[0], surface_cross_point_right[1], surface_cross_point_right[2]), 0.007, 1, 0, 0, "text_right_angle_average");
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();

	//m_mutex_pick = 1; //防止两次执行

#ifdef NETCOMMUNICATE
	double transferparam[4] = { parameter_[0] * 100,parameter_[1] * 100, parameter_[2], parameter_[6] };
	generalOutput ims;

	printf("current id : %d\n", m_sql_faceid_index);
	ims.paraLineParse(m_sql_faceid_index, "test.jpg", 0, transferparam, httpdouble, httplinestr);

	//ims.sumoutput("test.jpg", 0, personals, transferparam, httpdouble, httplinestr);
#endif // NETCOMMUNICATE

	//httpconnect ims; 
	//std::string drcfile = personname + ".drc";
	//ims.codeply(plyfile, drcfile, 8);
	//printf("mesh info:面数 %d, 顶点数 %d\n", (int)mesh.n_faces(), (int)mesh.n_vertices());
	//ims.httpinterface(transferparam, personname, personphone, personsex);
	//ims.uploadFile(personname, drcfile, 8);
	//std::remove(drcfile.data());
	//std::remove(plyfile.data());
}

void ditProcessPanel::clearAddShape()
{
	//pclViewer->removeShape("");
	pclViewer->removeAllShapes();

}


double ditProcessPanel::wideLineTwoPoint(ditVec3d& leftoutpoint, ditVec3d& rightoutpoint, ditVec3d leftpoint, ditVec3d linevector, ditVec3d linepoint, ditMesh & mesh, ditVec3d surfaceCoe, double surfaced)
{
	double leftstand = leftpoint.dot(surfaceCoe) + surfaced;
	double leftdist = 999;
	double rgithdist = 999;
	//double rightstand = rightpoint.dot(surfaceCoe) + surfaced;
	for (ditMesh::VertexIter vit = mesh.vertices_begin(); vit != mesh.vertices_end(); vit++)
	{
		ditMesh::Point p = mesh.point(*vit);
		ditVec3d vp(p[0], p[1], p[2]);
		double dpointjudge = vp.dot(surfaceCoe) + surfaced;
		double distacnelinepint = pointLineDistance(linevector, linepoint, vp);

		if ((dpointjudge*leftstand) >= 0) //left
		{
			if (leftdist > distacnelinepint)
			{
				leftdist = distacnelinepint;
				leftoutpoint = vp;
			}
		}
		else {//right
			if (rgithdist > distacnelinepint)
			{
				rgithdist = distacnelinepint;
				rightoutpoint = vp;
			}
		}
	}
	return cv::norm(leftoutpoint - rightoutpoint);
}


//线与平面的交点；
ditVec3d ditProcessPanel::surfaceLineCrossPoint(ditVec3d linevector, ditVec3d linepoint, ditVec3d face_vetex_coe, ditVec3d surfacepoint)
{
	//ditVec3d face_vetex_coe = linevector;
	double face_vetex_d = 0 - face_vetex_coe.dot(surfacepoint); //后端点的点right
	double t;
	t = (0 - ((face_vetex_coe.dot(linepoint)) + face_vetex_d)) / (face_vetex_coe.dot(linevector));

	ditVec3d  cross_point_right(linevector[0] * t + linepoint[0], linevector[1] * t + linepoint[1], linevector[2] * t + linepoint[2]);
	return cross_point_right;
}

//点与三维直线的垂直距离；
double ditProcessPanel::pointLineDistance(ditVec3d linevector, ditVec3d linepoint, ditVec3d asidepoint)
{
	double face_vetex_d = 0 - linevector.dot(asidepoint); //后端点的点right
	double t;
	t = (0 - ((linevector.dot(linepoint)) + face_vetex_d)) / (linevector.dot(linevector));

	ditVec3d  cross_point_right(linevector[0] * t + linepoint[0], linevector[1] * t + linepoint[1], linevector[2] * t + linepoint[2]);

	return cv::norm(cross_point_right - asidepoint);
}

void keyboardEvent(const pcl::visualization::KeyboardEvent& event, void* frame)
{
	if (event.getKeySym() == "space" && event.keyDown())
	{
		QKeyEvent *mEvnPress = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Space, Qt::KeyboardModifier::NoModifier);
		QApplication::sendEvent((ditProcessPanel*)frame, mEvnPress);
		delete[]mEvnPress;
		//viewFrame *pFrame = (viewFrame*)frame;
		//pFrame->icpIter();
	}
}
void mousedEvent(const pcl::visualization::MouseEvent& event, void* nothing)
{
	//viewFrame *pV = (viewFrame*)nothing;
	//	pV->pclViewer->get
}
void pickCallEvent(const pcl::visualization::PointPickingEvent& event, void* pFrame)
{
	if (event.getPointIndex() == -1)
		return;
	ditProcessPanel *p = (ditProcessPanel*)pFrame;
	ditPointT picked_point1, picked_point2;
	event.getPoint(picked_point1.x, picked_point1.y, picked_point1.z);
	//p->pclViewer->removeShape("handP");
	//pclViewer->addSphere(PointT(outFace3dPt[i][0], outFace3dPt[i][1], outFace3dPt[i][2]), 0.001, 255, 0, 0, tmpBuf);

	//p->pclViewer->addSphere(picked_point1, 0.001, 255, 0, 255, "handP");

	p->pclViewer->updateSphere(picked_point1, 0.001, 255, 0, 255, "handP");

	ditOffsetDlg InfoDlg(p);
	InfoDlg.initPickPoint(picked_point1);

	char tmpBuf[50];
	std::string tmpBufstring;

	sprintf(tmpBuf, "%f", picked_point1.x);
	InfoDlg.offsetX->setPlaceholderText(tmpBuf);
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();

	sprintf(tmpBuf, "%f", picked_point1.y);
	InfoDlg.offsetY->setPlaceholderText(tmpBuf);
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();

	sprintf(tmpBuf, "%f", picked_point1.z);
	InfoDlg.offsetZ->setPlaceholderText(tmpBuf);
	memset(tmpBuf, 0, sizeof(tmpBuf));
	tmpBufstring.clear();


	int r = InfoDlg.exec();

	if (r == QDialog::Accepted)
	{
		qDebug() << "Accepted";
	}
	else if (r == QDialog::Rejected)
	{
		qDebug() << "Rejected";
	}
	else
	{
		qDebug() << r;
	}

	//double sx, sy, sz;
	//sx = InfoDlg.offsetX->text().toDouble();

	//sy = InfoDlg.offsetY->text().toDouble();
	//sz = InfoDlg.offsetZ->text().toDouble();
	////默认不输入的情况下，为0count跟double 的值都为0；
	//printf("sx:  %f\n", sx);
	//printf("sy:  %f\n", sy);
	//printf("sz:  %f\n", sz);

	//PointT pick(picked_point1.x+sx, picked_point1.y + sy, picked_point1.z + sz);

	//p->m_picked_point = pick; //不断更新这个点；
	//p->addPoint(pick);
}



//Mat->QImage
QImage ConvertToQImage(const cv::Mat &mat)
{
	QImage img;
	int nChannel = mat.channels();
	if (nChannel == 3)
	{
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		img = QImage((const unsigned char*)mat.data, mat.cols, mat.rows, QImage::Format_RGB888);
	}
	else if (nChannel == 4)
	{
		img = QImage((const unsigned char*)mat.data, mat.cols, mat.rows, QImage::Format_ARGB32);
	}
	else if (nChannel == 1)
	{
		if (mat.cols % 4 != 0)
		{
			img = QImage(mat.cols + 4 - mat.cols % 4, mat.rows, QImage::Format_Indexed8);
			for (int i = 0; i < mat.rows; i++)
				memcpy(img.bits() + i * img.width(), mat.ptr(i), mat.cols);
		}
		else
			img = QImage((const unsigned char*)mat.data, mat.cols, mat.rows, QImage::Format_Indexed8);
	}
	return img;
}
void pclMesh2OpemMesh(pcl::PolygonMesh::Ptr pclMesh, void* oMesh)
{
	ditMesh *tMesh = (ditMesh*)oMesh;
	pcl::PointCloud<ditPointT> ptcloud;
	fromPCLPointCloud2(pclMesh->cloud, ptcloud);
	std::vector<OpenMesh::VertexHandle> ptHandleL;
	for (unsigned int i = 0; i < ptcloud.size(); i++)
	{
		ptHandleL.push_back(tMesh->add_vertex(OpenMesh::Vec3f(ptcloud[i].x, ptcloud[i].y, ptcloud[i].z)));
	}
	for (unsigned int i = 0; i < pclMesh->polygons.size(); i++)
	{
		std::vector<uint32_t> curFace = pclMesh->polygons[i].vertices;
		if (curFace.size() != 3)
			continue;
		tMesh->add_face(ptHandleL[curFace[0]], ptHandleL[curFace[1]], ptHandleL[curFace[2]]);
	}
	ditOutputDebugInfo("%d", tMesh->n_vertices());
	ditOutputDebugInfo("%d", tMesh->n_faces());
}