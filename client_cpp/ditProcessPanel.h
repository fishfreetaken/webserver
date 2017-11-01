#pragma once

#include <QtWidgets/QMainWindow>
#include "ditHeadScanner_global.h"
#include "InfoDlg.h"

#define NETCOMMUNICATE  //���������Ƿ��������ͨ�ţ������ļ��ϴ���������

class QVTKWidget;
class ditCaptureControl;
class imgShowWidget;
class ditCapturePanel;
class ditProcessPanel : public QWidget
{
	Q_OBJECT
public:
	ditProcessPanel(QWidget *parent = Q_NULLPTR);
	void icpIter();
	bool bAuthorized;

	QLabel *load_label;
	QTextBrowser *operate_text;
	QWidget *gridLayoutWidget;
	QGridLayout *Process_Grid;
	QPushButton *Return_Button;
	QPushButton *Save_Button;
	public slots:

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
	void createActions();
	void readSettings();
	void writeSettings();
	void openCloud();
	void keyPressEvent(QKeyEvent *event);

public:
	boost::shared_ptr<pcl::visualization::PCLVisualizer> pclViewer;

	ditPointT m_picked_point;//���ݱ�����
	void extractParametaers();
	void addPoint(ditPointT x);

	pcl::PolygonMesh::Ptr  outMesh;
	std::vector<ditVec3d>  outFace3dPt;
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr outCloud;

	int     m_sql_faceid_index;

private: //chendong  add for param calculate
	void PickoutFourParameter(std::vector<ditVec3d>&  s);//�������

	//int		m_mutex_pick;

	//void pushsinglepoint(ditVec3d p, std::vector<double> &arr);
	void PushSinglePoint(ditVec3d p, std::vector<std::vector<double>> &arr);


// 	std::vector<ditVec3d> face3dPt;
	std::vector<ditVec3d> face3dPt_pick;

	//ditResconstruct   *poffLineStruct = nullptr; //���ֻ��offline�����ߵ��أ�
	ditCapturePanel *caputrePanel = nullptr;


	double parameter_[7] = { 0,0,0,0,0,0,0 };//���յó����ĸ�������0��ͫ�ࣻ1��ͷ�����2��left������ߵ㣻3��right�������㣻4��left�۽ǽǶȣ�5��right�۽ǽǶȣ�
											 //std::vector<ditVec3d> face3dPt_; //
											 //void PickTwoEarPoints(PointT x);


private:	//���ߺ���
	ditVec3d	surfaceLineCrossPoint(ditVec3d linevector, ditVec3d linepoint, ditVec3d surfacepoint, ditVec3d face_vetex_coe);
	double		pointLineDistance(ditVec3d linevector, ditVec3d linepoint, ditVec3d asidepoint);
	double		wideLineTwoPoint(ditVec3d& leftoutpoint, ditVec3d& rightoutpoint, ditVec3d leftpoint, ditVec3d linevector, ditVec3d linepoint, ditMesh & mesh, ditVec3d surfaceCoe, double surfaced);
	void		clearAddShape();//����ӵ���״�������


};
void      keyboardEvent(const pcl::visualization::KeyboardEvent& event, void* frame);
void      mousedEvent(const pcl::visualization::MouseEvent& event, void* nothing);
void      pickCallEvent(const pcl::visualization::PointPickingEvent& event, void*);
void      CVtrans2pcl(const std::vector<ditVec3d> &retA, ditPointCloudT::Ptr& acloud);
//void      OpenMesh2pclMesh(void *pOMesh, pcl::PolygonMesh &mesh);
void      pclMesh2OpemMesh(pcl::PolygonMesh::Ptr pclMesh, void* oMesh);
