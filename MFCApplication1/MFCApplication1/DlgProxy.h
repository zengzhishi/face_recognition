
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CMFCApplication1Dlg;


// CMFCApplication1DlgAutoProxy ����Ŀ��

class CMFCApplication1DlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMFCApplication1DlgAutoProxy)

	CMFCApplication1DlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CMFCApplication1Dlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CMFCApplication1DlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMFCApplication1DlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

