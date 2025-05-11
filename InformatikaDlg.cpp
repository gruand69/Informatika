
// InformatikaDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Informatika.h"
#include "InformatikaDlg.h"
#include "afxdialogex.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "Idata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "initguid.h"
DEFINE_GUID(imageFormatBMP, 0xb96b3cab, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CInformatikaDlg



CInformatikaDlg::CInformatikaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFORMATIKA_DIALOG, pParent),
	m_A(0),
	m_B(0),
	m_C(0),
	m_D(0),
	m_E(0),
	m_Acc(0.001),
	m_NumDigits(3)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInformatikaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_A, m_EditA);
	DDX_Control(pDX, IDC_EDIT_B, m_EditB);
	DDX_Control(pDX, IDC_EDIT_C, m_EditC);
	DDX_Control(pDX, IDC_EDIT_D, m_EditD);
	DDX_Control(pDX, IDC_EDIT_E, m_EditE);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
}

BEGIN_MESSAGE_MAP(CInformatikaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_A, &CInformatikaDlg::OnEnChangeEditA)
	ON_EN_CHANGE(IDC_EDIT_B, &CInformatikaDlg::OnEnChangeEditB)
	ON_EN_CHANGE(IDC_EDIT_C, &CInformatikaDlg::OnEnChangeEditC)
	ON_EN_CHANGE(IDC_EDIT_D, &CInformatikaDlg::OnEnChangeEditD)
	ON_EN_CHANGE(IDC_EDIT_E, &CInformatikaDlg::OnEnChangeEditE)
	ON_EN_CHANGE(IDC_EDIT2, &CInformatikaDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BTN_ANIME, &CInformatikaDlg::OnBnClickedBtnAnime)
	ON_CBN_SELCHANGE(IDC_COMBO_COL, &CInformatikaDlg::OnCbnSelchangeComboCol)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_32771, &CInformatikaDlg::On32771)
	ON_COMMAND(ID_32772, &CInformatikaDlg::On32772)
	ON_COMMAND(ID_32773, &CInformatikaDlg::On32773)
	ON_BN_CLICKED(IDOK, &CInformatikaDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CInformatikaDlg

BOOL CInformatikaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	m_artist.SubclassDlgItem(IDD_ARTIST, this);
	CRect rc;
	m_artist.GetClientRect(&rc);
	m_Trans.SetTransParam(rc.Width(), rc.Height());
	m_artist.SetIdataPtr(this);
	m_artist.SetCalculation(&m_Calculation, &params, &m_Trans);
	m_artist.SetParams(&params);

	CWinApp* pApp = AfxGetApp();

	m_A = pApp->GetProfileIntW(_T("Settings"), _T("Amplitude"), 10) / 10.;
	CString strT;
	strT.Format(L"%.1f", m_A);
	m_EditA.SetWindowTextW(strT);

	int nSel = pApp->GetProfileIntW(_T("Settings"), _T("Combo"), 0);

	m_B = pApp->GetProfileIntW(_T("Settings"), _T("Frequency"), 10) / 10.;
	strT.Format(L"%.1f", m_B);
	m_EditB.SetWindowTextW(strT);

	m_C = pApp->GetProfileIntW(_T("Settings"), _T("Intersection"), 10) / 10.;
	strT.Format(L"%.1f", m_C);
	m_EditC.SetWindowTextW(strT);

	m_D = pApp->GetProfileIntW(_T("Settings"), _T("Rate"), 10) / 10.;
	strT.Format(L"%.1f", m_D);
	m_EditD.SetWindowTextW(strT);

	CString strPoint = pApp->GetProfileString(_T("Settings"), _T("Point"), _T("0"));

	if (strPoint.IsEmpty())
		strPoint = _T("0");
	m_E = _wtoi(strPoint) / 10.;
	strT.Format(L"%.1f", m_E);
	m_EditE.SetWindowTextW(strT);


	m_Acc = pApp->GetProfileIntW(_T("Settings"), _T("Accuracy"), 10) / 1000.0;
	if (m_Acc <= 0.0)
		m_Acc = 0.0001;
	strT.Format(L"%.3f", m_Acc);
	m_Edit2.SetWindowTextW(strT);

	CComboBox* pCmb = (CComboBox*)GetDlgItem(IDC_COMBO_COL);
	if (pCmb)
	{
		pCmb->SetCurSel(0);
		OnCbnSelchangeComboCol();
	}
	bCreated = true;
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CInformatikaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CInformatikaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CInformatikaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CInformatikaDlg::OnEnChangeEditA()
{
	CString strT;
	m_EditA.GetWindowTextW(strT);
	m_A = _wtof(strT);
	params.a = m_A;
	Calc();
	m_artist.Invalidate();
}

void CInformatikaDlg::OnEnChangeEditB()
{
	CString strT;
	m_EditB.GetWindowTextW(strT);
	m_B = _wtof(strT);
	params.b = m_B;
	Calc();
	m_artist.Invalidate();
}

void CInformatikaDlg::OnEnChangeEditC()
{
	CString strT;
	m_EditC.GetWindowTextW(strT);
	m_C = _wtof(strT);
	params.c = m_C;
	Calc();
	m_artist.Invalidate();
}

void CInformatikaDlg::OnEnChangeEditD()
{
	CString strT;
	m_EditD.GetWindowTextW(strT);
	m_D = _wtof(strT);
	params.d = m_D;
	Calc();
	m_artist.Invalidate();
}

void CInformatikaDlg::OnEnChangeEditE()
{
	CString strT;
	m_EditE.GetWindowTextW(strT);
	m_E = _wtof(strT);
	params.e = m_E;
	Calc();
	m_artist.Invalidate();
}

void CInformatikaDlg::OnEnChangeEdit2()
{
	CString strDigits;
	m_Edit2.GetWindowText(strDigits);


	int userPrecision = _wtof(strDigits);

	if (userPrecision < 1)
	{
		userPrecision = 3;
		m_Edit2.SetWindowText(_T("3"));
	}

	m_NumDigits = userPrecision;

	m_artist.SetPrecision(m_NumDigits);
	Calc();
	m_artist.Invalidate();
}

void CInformatikaDlg::OnBnClickedBtnAnime()
{
	const int target_fps = 144;
	const int debug_factor = 1.6;
	int delay_ms = static_cast<int>((1000 / target_fps) * debug_factor);
	CButton* pB = (CButton*)GetDlgItem(IDC_BTN_ANIME);
	if (pB)
	{
		if (pB->GetCheck())
			SetTimer(ID_TIMERA, delay_ms, nullptr);
		else
			KillTimer(ID_TIMERA);
	}
}

void CInformatikaDlg::OnCbnSelchangeComboCol()
{
	CComboBox* pCmb = (CComboBox*)GetDlgItem(IDC_COMBO_COL);
	if (pCmb) 
	{
		int nSel = pCmb->GetCurSel();
		switch (nSel)
		{
		case 0:
			m_artist.SetBkColor(RGB(30, 30, 30));
			m_artist.SetAxisColor(RGB(220, 220, 220));
			m_artist.SetSinColor(RGB(0, 128, 255));
			m_artist.SetLinearColor(RGB(255, 165, 0));
			break;
		case 1:
			m_artist.SetBkColor(RGB(255, 255, 255));
			m_artist.SetAxisColor(RGB(0, 0, 0));
			m_artist.SetSinColor(RGB(0, 0, 200));
			m_artist.SetLinearColor(RGB(200, 0, 0));
			break;
		case 2:
			m_artist.SetBkColor(RGB(230, 230, 250));
			m_artist.SetAxisColor(RGB(75, 0, 130));
			m_artist.SetSinColor(RGB(0, 160, 0));
			m_artist.SetLinearColor(RGB(220, 20, 60));
			break;
		default:
			break;
		}
		m_artist.SetRedrawFlag(true);
		m_artist.RedrawWindow();
	}
}

size_t CInformatikaDlg::GetSinPoints(std::vector<CPoint>& vecPt)
{
	vecPt = m_vecPt;
	return m_vecPt.size();
}

size_t CInformatikaDlg::GetLinearPoints(std::vector<CPoint>& vecPt)
{
	vecPt = m_vecLinear;
	return m_vecLinear.size();
}

bool CInformatikaDlg::Calc()
{
	m_vecPt.clear();
	m_vecLinear.clear();

	CRect rc;
	m_artist.GetClientRect(&rc);
	if (rc.Width() <= 2 * BORDER_W) return false;
	double step = (2.0 * M_PI) / (rc.Width() - 2 * BORDER_W);
	int NumPoints = static_cast<int>((2.0 * M_PI) / step);
	double scaleX = (rc.Width() - 2 * BORDER_W) / (2.0 * M_PI);
	double scaleY = rc.Height() / 4.0;

	Parameters sinParams;
	sinParams.a = m_A;
	sinParams.b = m_B;
	sinParams.c = m_C;
	sinParams.d = 0.0;
	sinParams.e = 0.0;

	Parameters linearParams;
	linearParams.a = 0.0;
	linearParams.b = 0.0;
	linearParams.c = 0.0;
	linearParams.d = m_D;
	linearParams.e = m_E;
	
	for (double X = -M_PI/*0.*/; X < /*2.0 */ M_PI; X += step)
	{
		CPoint ptSin = m_Trans.Trans(X, sinParams);
		m_vecPt.push_back(ptSin);

		CPoint ptLinear = m_Trans.Trans(X, linearParams);
		m_vecLinear.push_back(ptLinear);
	}
	
	return !m_vecPt.empty() && !m_vecLinear.empty();
}

void CInformatikaDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (bCreated)
	{
		CRect rc;
		m_artist.GetClientRect(&rc);
		m_Trans.SetTransParam(rc.Width(), rc.Height());
		Calc();
	}
	//__super::OnSize(nType, cx, cy);

}

size_t CInformatikaDlg::IGetSinPoints(std::vector<CPoint>& vec)
{
	return GetSinPoints(vec);
}

size_t CInformatikaDlg::IGetLinearPoints(std::vector<CPoint>& vec)
{
	return GetLinearPoints(vec);
}

void CInformatikaDlg::OnTimer(UINT_PTR nIDEvent)
{
	m_A += 0.01;
	m_B += M_PI / 180;
	m_C += 0.01;
	m_D += 0.01;
	m_E -= 0.01;

	Calc();
	m_artist.Invalidate();

	CString str;

	str.Format(_T("%.2f"), m_A);
	m_EditA.SetWindowText(str);

	str.Format(_T("%.2f"), m_B);
	m_EditB.SetWindowText(str);

	str.Format(_T("%.2f"), m_C);
	m_EditC.SetWindowText(str);

	str.Format(_T("%.2f"), m_D);
	m_EditD.SetWindowText(str);

	str.Format(_T("%.2f"), m_E);
	m_EditE.SetWindowText(str);

	TRACE("Timer\n");
	__super::OnTimer(nIDEvent);
}

void CInformatikaDlg::On32771()
{
	CDC MemDc;
	CBitmap BitMap;
	CDC* pDca = m_artist.GetDC();
	MemDc.CreateCompatibleDC(pDca);

	CRect rc;
	m_artist.GetClientRect(&rc);
	BitMap.CreateCompatibleBitmap(pDca, rc.Width(), rc.Height());
	HGDIOBJ ob = MemDc.SelectObject(&BitBlt);
	MemDc.BitBlt(0, 0, rc.Width(), rc.Height(), pDca, 0, 0, SRCCOPY);
	m_artist.ReleaseDC(pDca);
	MemDc.SelectObject(ob);
	static wchar_t szFilter[] = _T("BMP files (*.bmp)|*.bmp||");
	CFileDialog dlg(FALSE, _T("bmp"), NULL, 6, szFilter);
	if (IDOK == dlg.DoModal())
	{
		CImage image;
		image.Attach(HBITMAP(BitMap));
		CString strFull = dlg.GetOFN().lpstrFile;
		HRESULT hr = image.Save(strFull, imageFormatBMP);
		if (S_OK == hr)
			AfxMessageBox(_T("Изображение успешно сохранено"), MB_ICONINFORMATION);	
	}
	else
		AfxMessageBox(_T("Вы забыли сохранить изображение!"), MB_ICONINFORMATION);
}

void CInformatikaDlg::On32772()
{
	OnBnClickedOk();
	//OnOK();
}

void CInformatikaDlg::On32773()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CInformatikaDlg::OnBnClickedOk()
{
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt(_T("Settings"), _T("Amplitude"), floor(m_A * 10 + .5));
	pApp->WriteProfileInt(_T("Settings"), _T("Frequency"), floor(m_B * 10 + .5));
	pApp->WriteProfileInt(_T("Settings"), _T("Intersection"), floor(m_C * 10 + .5));
	pApp->WriteProfileInt(_T("Settings"), _T("Rate"), floor(m_D * 10 + .5));

	CString strPoint;
	strPoint.Format(_T("%d"), static_cast<int>(floor(m_E * 10 + 0.5)));
	pApp->WriteProfileString(_T("Settings"), _T("Point"), strPoint);

	pApp->WriteProfileInt(_T("Settings"), _T("AccuracyDigits"), m_NumDigits);
	pApp->WriteProfileInt(_T("Settings"), _T("Accuracy"), static_cast<int>(m_Acc * 1000.0));

	CComboBox* pCmb = (CComboBox*)GetDlgItem(IDC_COMBO_COL);
	if (pCmb)
	{
		int nSel = pCmb->GetCurSel();
		pApp->WriteProfileInt(_T("Settings"), _T("Combo"), nSel);
	}
	CDialogEx::OnOK();
}
