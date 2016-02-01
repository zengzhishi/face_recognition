#include "stdafx.h"
#include "VEDIO.h"


CVEDIODS::CVEDIODS()
{
	Width = 0;
	Hight = 0;


}
CVEDIODS::~CVEDIODS()
{

}

void CVEDIODS::openCamera(UINT ID, CDC* pDC, CRect &rect)//�����ڵĺ�����.h�ļ��������������
{
	//�˴���ӹ��ڴ�����ͷ����غ���
	if (1)
	{
		/*
		VideoCapture capture(0);
		CascadeClassifier cascade;
		cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml");
		Face_Catch fc;*/
		Mat face = imread("C:/boldt.jpg",1);
//		fc.get_Face_Frame(face, capture, cascade, 1.3);
		showImage(face, ID, pDC, rect);
	//	waitKey(1000);
	}
}

void CVEDIODS::showImage(Mat &img, UINT ID, CDC* pDC, CRect &rect)
{
	pDC->GetWindow()->GetWindowRect(&rect);
//	CDC* pDC = GetDlgItem(ID)->GetDC();// �����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();// ��ȡ HDC(�豸���) �����л�ͼ����

//	CRect rect;
//	GetDlgItem(ID)->GetClientRect(&rect);
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
	ReleaseDC(pDC);
}

