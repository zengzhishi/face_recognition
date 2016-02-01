// DIANMING.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DIANMING.h"
#include "afxdialogex.h"




// DIANMING �Ի���

IMPLEMENT_DYNAMIC(DIANMING, CDialogEx)

DIANMING::DIANMING(CWnd* pParent /*=NULL*/)
	: CDialogEx(DIANMING::IDD, pParent)
	, nameget(_T(""))
	, sexget(_T(""))
	, specialtyget(_T(""))
	, IDget(_T(""))
	, classroomget(_T(""))
{

}

DIANMING::~DIANMING()
{
}

void DIANMING::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, nameget);
	DDX_Text(pDX, IDC_EDIT2, sexget);
	DDX_Text(pDX, IDC_EDIT3, specialtyget);
	DDX_Text(pDX, IDC_EDIT4, IDget);
	DDX_Text(pDX, IDC_EDIT6, classroomget);
}


BEGIN_MESSAGE_MAP(DIANMING, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &DIANMING::OnEnChangeEdit1)
	ON_BN_CLICKED(IDCANCEL, &DIANMING::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &DIANMING::OnBnClickedButton1)
END_MESSAGE_MAP()


// DIANMING ��Ϣ�������


void DIANMING::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void DIANMING::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here


	CDialogEx::OnCancel();
}


void DIANMING::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	CDC* pDC = GetDlgItem(IDC_PIC2)->GetDC();
	HDC hDC = pDC->GetSafeHdc();

	Mat img, face;
	CRect rect;
	GetDlgItem(IDC_PIC2)->GetClientRect(&rect);
	VideoCapture capture(0);
	CascadeClassifier cascade;
	cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml");
	Face_Catch fc;

	fc.get_Face_Frame(img, face, capture, cascade, 1.3);
	draw_Image(pDC, hDC, img, rect);

	ConMySQL mysql_server;
	stu_info stu[10];
	int stuNum = mysql_server.get_all_Info(stu);
	
	Ptr<FaceRecognizer> model = face::createLBPHFaceRecognizer();
	fc.standsize = imread(stu[0].path[0]).size();
	if (!fc.load_Reco_Data(model))
	{
		vector<Mat> trainFace;
		vector<int> trainlabel;
		for (int i = 0; i < stuNum; ++i)
		{
			trainFace.push_back(imread(stu[i].path[0], 0));
			trainFace.push_back(imread(stu[i].path[1], 0));
			trainFace.push_back(imread(stu[i].path[2], 0));
			trainFace.push_back(imread(stu[i].path[3], 0));
			for (int j = 0; j < 4;++j)
				trainlabel.push_back(i);
		}
		fc.face_Reco_Train(model, trainFace, trainlabel, fc.standsize);
	}
	try{
		face = fc.resize_norm(face, fc.standsize);
		int num = model->predict(face);
		if (num != -1)
		{
			nameget = stu[num].name.c_str();
			if (stu[num].sex)
				sexget = "��";
			else
				sexget = "Ů";
			specialtyget = stu[num].specialty.c_str();
			IDget = stu[num].id.c_str();
			classroomget = stu[num].classname.c_str();
		}

		//fc.face_Reco_Train
		GetDlgItem(IDC_EDIT1)->SetWindowText(nameget);
		GetDlgItem(IDC_EDIT2)->SetWindowText(sexget);
		GetDlgItem(IDC_EDIT3)->SetWindowText(specialtyget);
		GetDlgItem(IDC_EDIT4)->SetWindowText(IDget);
		GetDlgItem(IDC_EDIT6)->SetWindowText(classroomget);
		GetDlgItem(IDC_TEXT_ERROR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TEXT_FINE)->ShowWindow(SW_SHOW);
	}
	catch (Exception e){
		GetDlgItem(IDC_TEXT_ERROR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TEXT_FINE)->ShowWindow(SW_HIDE);
	}
	


}


void DIANMING::draw_Image(CDC* pDC, HDC hDC, Mat img, CRect rect)
{
	int rw = rect.right - rect.left;// ���ͼƬ�ؼ��Ŀ�͸�
	int rh = rect.bottom - rect.top;

	int iw = img.size().width;// ��ȡͼƬ�Ŀ�͸�
	int ih = img.size().height;
	if (rw > iw && rh > ih)
	{

	}
	else
	{
		CvSize size;
		size.height = rh;
		size.width = rw;
		resize(img, img, size);
		iw = rw;
		ih = rh;
	}
	int tx = (int)(rw - iw) / 2;// ʹͼƬ����ʾλ�������ڿؼ�������
	int ty = (int)(rh - ih) / 2;

	SetRect(rect, tx, ty, tx + iw, ty + ih);
	CvvImage cimg;
	IplImage img1 = img;
	cimg.CopyOf(&img1);
	cimg.DrawToHDC(hDC, &rect);


}