#pragma once
#include "Face_Catch.h"
#include "ConMySQL.h"
#include "CvvImage.h"

using namespace cv;
// DIANMING �Ի���

class DIANMING : public CDialogEx
{
	DECLARE_DYNAMIC(DIANMING)

public:
	DIANMING(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DIANMING();

// �Ի�������
	enum { IDD = IDD_DIANMING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();

	void draw_Image(CDC* pDC, HDC hDC, Mat img, CRect rect);

	CString nameget;
	CString sexget;
	CString specialtyget;
	CString IDget;
	CString classroomget;
};
