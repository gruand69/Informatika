
// InformatikaDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Informatika.h"
#include "InformatikaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	: CDialogEx(IDD_INFORMATIKA_DIALOG, pParent)
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
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the __super::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}

void CInformatikaDlg::OnEnChangeEditB()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the __super::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}

void CInformatikaDlg::OnEnChangeEditC()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the __super::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}

void CInformatikaDlg::OnEnChangeEditD()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the __super::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}

void CInformatikaDlg::OnEnChangeEditE()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the __super::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}

void CInformatikaDlg::OnEnChangeEdit2()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the __super::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}

void CInformatikaDlg::OnBnClickedBtnAnime()
{
	// TODO: добавьте свой код обработчика уведомлений
}

void CInformatikaDlg::OnCbnSelchangeComboCol()
{
	// TODO: добавьте свой код обработчика уведомлений
}

size_t CInformatikaDlg::GetSinPoints(std::vector<CPoint>& vecPt)
{
	// TODO: Добавьте сюда код реализации.
	return size_t();
}

size_t CInformatikaDlg::GetLinearPoints(std::vector<CPoint>& vecPt)
{
	// TODO: Добавьте сюда код реализации.
	return size_t();
}

bool CInformatikaDlg::Calc()
{
	// TODO: Добавьте сюда код реализации.
	return false;
}

void CInformatikaDlg::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: добавьте свой код обработчика сообщений
}

size_t CInformatikaDlg::IGetSinPoints(std::vector<CPoint>& vec)
{
	// TODO: Добавьте сюда код реализации.
	return size_t();
}

size_t CInformatikaDlg::IGetLinearPoints(std::vector<CPoint>& vec)
{
	// TODO: Добавьте сюда код реализации.
	return size_t();
}

void CInformatikaDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	__super::OnTimer(nIDEvent);
}

void CInformatikaDlg::On32771()
{
	// TODO: Сохранение
}

void CInformatikaDlg::On32772()
{
	OnOK();
}

void CInformatikaDlg::On32773()
{
	CAboutDlg dlg;
	dlg.DoModal();
}
