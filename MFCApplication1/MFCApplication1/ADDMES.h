#pragma once
#include "afxwin.h"
#include "ConMySQL.h"

// CADDMES �Ի���

class CADDMES : public CDialogEx
{
	DECLARE_DYNAMIC(CADDMES)

public:
	CADDMES(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CADDMES();

// �Ի�������
	enum { IDD = IDD_ADDMES1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	// ����ӵ���Ϣ
	CString ADDSEX;
	afx_msg void OnCbnDropdownCombo1();
	CComboBox COMBOADDSEX;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnStnEnablePic1();
	afx_msg void OnBnClickedOk();

	void draw_Image(CDC* pDC, HDC hDC, Mat img, CRect rect);

	CString namead;
	CString specialty;
	CString ID;
	CString classroom;
	ConMySQL mysqlserver;
};
