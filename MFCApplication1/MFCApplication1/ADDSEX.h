#pragma once
#include "afxwin.h"


// ADDSEX �Ի���

class ADDSEX : public CDialogEx
{
	DECLARE_DYNAMIC(ADDSEX)

public:
	ADDSEX(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ADDSEX();

// �Ի�������
	enum { IDD = IDD_ADDMES1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	// �ؼ�����of ADDSEX
	CComboBox COMBOADDSEX;
	afx_msg void OnDropdownCombo1();
};
