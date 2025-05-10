
// InformatikaDlg.h: файл заголовка
//

#pragma once
#include "CArtist.h"

#define ID_TIMERA 40


// Диалоговое окно CInformatikaDlg
class CInformatikaDlg : public CDialogEx
	, Idata
{
// Создание
public:
	CInformatikaDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFORMATIKA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	CCalculation m_Calculation;
	Parameters params;
public:
	CArtist m_artist;
	CEdit m_EditA;
	CEdit m_EditB;
	CEdit m_EditC;
	CEdit m_EditD;
	CEdit m_EditE;
	CEdit m_Edit2;
	afx_msg void OnEnChangeEditA();
	afx_msg void OnEnChangeEditB();
	afx_msg void OnEnChangeEditC();
	afx_msg void OnEnChangeEditD();
	afx_msg void OnEnChangeEditE();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedBtnAnime();
	afx_msg void OnCbnSelchangeComboCol();
	size_t GetSinPoints(std::vector<CPoint>& vecPt);
	size_t GetLinearPoints(std::vector<CPoint>& vecPt);
	double m_A;
	double m_B;
	double m_C;
	double m_D;
	double m_E;
	double m_Acc;
	int m_NumDigits;
protected:
	CTrans m_Trans;
	std::vector<CPoint> m_vecPt;
	std::vector<CPoint> m_vecLinear;
	bool Calc();
	bool bCreated;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual size_t IGetSinPoints(std::vector<CPoint>& vec);
	virtual size_t IGetLinearPoints(std::vector<CPoint>& vec);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void OnBnClickedOk();
};
