// ADDMES.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ADDMES.h"
#include "afxdialogex.h"
#include <iostream>
#include "VEDIO.h"
#include "NEEDMOREMESSAGE.h"

int get_face_times = 0;
bool flag1 = true;
// CADDMES �Ի���

IMPLEMENT_DYNAMIC(CADDMES, CDialogEx)

CADDMES::CADDMES(CWnd* pParent /*=NULL*/)
	: CDialogEx(CADDMES::IDD, pParent)
	, ADDSEX(_T(""))
	, namead(_T(""))
	, specialty(_T(""))
	, ID(_T(""))
	, classroom(_T(""))
{

}

CADDMES::~CADDMES()
{
}

void CADDMES::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, ADDSEX);
	DDX_Control(pDX, IDC_COMBO1, COMBOADDSEX);
	SetDlgItemText(IDC_COMBO1, _T("��ѡ��"));
	DDX_Text(pDX, IDC_EDIT1, namead);
	DDX_Text(pDX, IDC_EDIT4, specialty);
	DDX_Text(pDX, IDC_EDIT2, ID);
	DDX_Text(pDX, IDC_EDIT3, classroom);
}


BEGIN_MESSAGE_MAP(CADDMES, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CADDMES::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CADDMES::OnCbnSelchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CADDMES::OnCbnDropdownCombo1)
	ON_EN_CHANGE(IDC_EDIT1, &CADDMES::OnEnChangeEdit1)
	ON_STN_ENABLE(IDC_PIC1, &CADDMES::OnStnEnablePic1)
	ON_BN_CLICKED(IDOK, &CADDMES::OnBnClickedOk)
END_MESSAGE_MAP()


// CADDMES ��Ϣ�������
CVEDIODS vedios;

void CADDMES::OnBnClickedButton1()
{/*
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	char path[100];
	int ret = 1;
	//��ý�ȡ��ͼ��
	//���num(int��)
	if (pic_num == 1)
	{
		FILE* dataFile = NULL;

		ret = sprintf(path, ".\\picture\\%d", num/*��ȡ��numֵ);
		_mkdir(path);
		//����ͼ���ļ�����������pic_num��ʾΪ�ڼ���
	}
	for (; 1<pic_num <= 4; pic_num++)
	{
		ret = sprintf(path, ".\\picture\\%d", num/*ͬ��);
		//ͬ�Ϸ�������ͼ���ļ�

	}
	*/
	CDC* pDC = GetDlgItem(IDC_PIC1)->GetDC();
	HDC hDC = pDC->GetSafeHdc();

	Mat img, face;
	CRect rect;
	GetDlgItem(IDC_PIC1)->GetClientRect(&rect);
	VideoCapture capture(0);
	CascadeClassifier cascade;
	cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml");
	Face_Catch fc;

	fc.get_Face_Frame(img, face, capture, cascade, 1.3);
	draw_Image(pDC, hDC, img, rect);

	ReleaseDC(pDC);
}



void CADDMES::draw_Image(CDC* pDC, HDC hDC, Mat img, CRect rect)
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


void CADDMES::OnCbnSelchangeCombo1()//�����Ϣ�е��Ա�ѡ�
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CADDMES::OnCbnDropdownCombo1()
{
	
	if (flag1){
		COMBOADDSEX.AddString(_T("Ů"));
		COMBOADDSEX.AddString(_T("��"));
		COMBOADDSEX.AddString(_T("��ѡ��"));
		COMBOADDSEX.SetCurSel(0);
		flag1 = false;
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CADDMES::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CADDMES::OnStnEnablePic1()
{
	// TODO: Add your control notification handler code here
//	CDC* pDC1 = GetDC();
//	vedios.openCamera(IDC_PIC1, pDC1, );
}


void CADDMES::OnBnClickedOk()
{
	
	// TODO: Add your control notification handler code here
	while (1){
		bool flag = true;
		if (!GetDlgItemText(IDC_EDIT1, namead)){ flag = false; }
		if (!GetDlgItemText(IDC_COMBO1, ADDSEX)){ flag = false; }
		if (!GetDlgItemText(IDC_EDIT2, ID)){ flag = false; }
		if (!GetDlgItemText(IDC_EDIT3, classroom)){ flag = false; }
		if (!GetDlgItemText(IDC_EDIT4, specialty)){ flag = false; }
		if (flag)
		{

			bool a = true;//true �� false Ů

			if (_tcscmp(ADDSEX, _T("��")) != 0 || _tcscmp(ADDSEX, _T("��ѡ��")))
			{
				a = false;
			}
			stu_info stu;
			stu.name = mysqlserver.ch_CStringToString(namead);
			stu.id = mysqlserver.ch_CStringToString(ID);
			stu.classname = mysqlserver.ch_CStringToString(classroom);
			stu.specialty = mysqlserver.ch_CStringToString(specialty);
			stu.sex = a;


//			string present_data;
			mysqlserver.ch_present_time(3);
//			mysqlserver.get_present_time_data(present_data);
//			int p = mysqlserver.update_present_time();
			mysqlserver.insert_Stu_Info_full(stu);
//			stu_info stu1[10];
//			for (int j = 0; j < 4;j++)
//				stu.path[j] = "sdjlfjl";
//			string path23 = "D:/Face/face_detected/face_eigen_data/faceRecognition.xml";
//			mysqlserver.get_all_Info(stu1);
//			mysqlserver.get_Reco_Data_Size();
//			mysqlserver.update_Reco_Data(path23, 200, 200);

			CDialogEx::OnOK();
		}
		else{
			NEEDMOREMESSAGE NM;
			NM.DoModal();
			break;
		}
	}


	/*
	CDialogEx::OnOK();
	GetDlgItemText(IDC_EDIT1, namead);
	GetDlgItemText(IDC_COMBO1, ADDSEX);
	GetDlgItemText(IDC_EDIT2, ID);
	GetDlgItemText(IDC_EDIT3, classroom);
	GetDlgItemText(IDC_EDIT4, specialty);

	bool a = true;//true �� false Ů

	if (_tcscmp(ADDSEX, _T("��")) != 0)
	{
		a = false;
	}


	ConMySQL mysqlserver;
	mysqlserver.chCon("localhost", "root", "948926865", "face_detected", 3306);

	stu_info stu[10];
	/*
	stu.name = mysqlserver.ch_CStringToString(namead);
	stu.id = mysqlserver.ch_CStringToString(ID);
	stu.classname = mysqlserver.ch_CStringToString(classroom);
	stu.specialty = mysqlserver.ch_CStringToString(specialty);
	stu.sex = a;

	mysqlserver.insert_Stu_Info_full(stu);
	*/
	//mysqlserver.get_all_Info(stu);

}
