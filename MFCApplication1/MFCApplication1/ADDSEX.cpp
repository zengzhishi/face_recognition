// ADDSEX.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ADDSEX.h"
#include "afxdialogex.h"


// ADDSEX �Ի���

IMPLEMENT_DYNAMIC(ADDSEX, CDialogEx)

ADDSEX::ADDSEX(CWnd* pParent /*=NULL*/)
	: CDialogEx(ADDSEX::IDD, pParent)
{
	
}

ADDSEX::~ADDSEX()
{
	
}

void ADDSEX::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, COMBOADDSEX);
	
}


BEGIN_MESSAGE_MAP(ADDSEX, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ADDSEX::OnCbnSelchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &ADDSEX::OnDropdownCombo1)
END_MESSAGE_MAP()


// ADDSEX ��Ϣ�������

void ADDSEX::OnDropdownCombo1()
{
	COMBOADDSEX.AddString(_T("��ѡ��"));
	COMBOADDSEX.AddString(_T("��"));
	COMBOADDSEX.AddString(_T("Ů"));
	COMBOADDSEX.SetCurSel(0);
	SetDlgItemText(IDC_COMBO1, _T("��ѡ��"));
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void ADDSEX::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}



