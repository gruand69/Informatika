#include "pch.h"
#include "CArtist.h"


CArtist::CArtist()
{
	m_bkCol = RGB(255, 255, 255);
	m_AxisColor = RGB(0, 0, 0);
	m_SinColor = RGB(0, 0, 255);
	m_LinearColor = RGB(255, 0, 0);
}

CArtist::~CArtist()
{
	if (m_MemDc)
		delete m_MemDc;
	if (m_BitMap)
		delete m_BitMap;
}
void CArtist::SetParams(Parameters* params)
{
	m_params = params;
}

void CArtist::SetCalculation(CCalculation* calc, Parameters* params, CTrans* trans)
{
	m_Calculation = calc;
	m_params = params;
	m_Trans = trans;
}
BEGIN_MESSAGE_MAP(CArtist, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CArtist::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_params)
	{
		AfxMessageBox(_T("Параметры не заданы."));
		return;
	}
	if (m_params->a == 0.0 && m_params->b == 0.0 && m_params->c == 0.0 && 
		m_params->d == 0.0 && m_params->e == 0.0)
	{
		AfxMessageBox(_T("Графики не определены (параметры равны 0."));
		return;
	}

	double clickX = m_Trans->ScreenToMathX(point.x);

	double searchRadius = 1.0;
	double left = clickX - searchRadius;
	double right = clickX + searchRadius;
	double step = 0.1;
	int iteration = 0;
	double closesRoot = 0.0;
	double minDistance = DBL_MAX;
	bool rootFound = false;
	double epsilon = 0.5 * pow(10.0, -GetPrecision());

	for (double x = left; x <= right; x += step)
	{
		if (m_Calculation->GetDifference(x, *m_params) *
			m_Calculation->GetDifference(x + step, *m_params) <= 0)
		{
			double root = m_Calculation->FindRoot(x, x + step, *m_params, epsilon, iteration);
			double distance = fabs(root - clickX);
				if (distance < minDistance)
				{
					minDistance = distance;
					closesRoot = root;
					rootFound = true;
				}
				x += step;
		}
	}
	if (rootFound)
	{
		CString message;
		int precision = GetPrecision();
		message.Format(_T("Ближайший корень: %.*f\nКоличество итераций: %d"), precision, closesRoot, iteration);
		AfxMessageBox(message);
	}
	else
	{
		AfxMessageBox(_T("В выбранной области корней не найдено."));
	}
	CStatic::OnLButtonDown(nFlags, point);
}

void CArtist::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);

	CRgn reg;
	reg.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 20, 20);
	dc.SelectClipRgn(&reg);

	CDC memDc;
	memDc.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	CBitmap* pOldBmp = memDc.SelectObject(&bitmap);

	memDc.FillSolidRect(&rc, m_bkCol);
	//dc.FillSolidRect(&rc, m_bkCol);


	{
		CPen penAxis;
		penAxis.CreatePen(PS_SOLID, 3, m_AxisColor);
		CPen* pOldPen = memDc.SelectObject(&penAxis);
		memDc.MoveTo(rc.left + BORDER_W, rc.CenterPoint().y);
		memDc.LineTo(rc.right - BORDER_W, rc.CenterPoint().y);
		memDc.MoveTo(rc.CenterPoint().x, rc.top + BORDER_W);
		memDc.LineTo(rc.CenterPoint().x, rc.bottom - BORDER_W);
		memDc.SelectObject(pOldPen);
		
		//CPen penAxis;
		//penAxis.CreatePen(PS_SOLID, 3, m_AxisColor);
		//CPen* pOldPen = dc.SelectObject(&penAxis);
		//dc.MoveTo(rc.left + BORDER_W, rc.CenterPoint().y);
		//dc.LineTo(rc.right - BORDER_W, rc.CenterPoint().y);
		//dc.MoveTo(rc.CenterPoint().x, rc.top + BORDER_W);
		//dc.LineTo(rc.CenterPoint().x, rc.bottom - BORDER_W);
		//dc.SelectObject(pOldPen);
	}

	{
		CFont font;
		font.CreatePointFont(90, _T("Arial"));
		CFont* pOldFont = memDc.SelectObject(&font);

		COLORREF oldTextColor = memDc.SetTextColor(m_AxisColor);

		CPen tickPen;
		tickPen.CreatePen(PS_SOLID, 1, m_AxisColor);
		CPen* pOldPenTick = memDc.SelectObject(&tickPen);

		int xOrigin = rc.CenterPoint().x;
		int yOrigin = rc.CenterPoint().y;

		//double maxMathX = (rc.right - xOrigin - BORDER_W) / m_Trans->m_ScaleX;
		//double minMathX = (rc.left + BORDER_W - xOrigin ) / m_Trans->m_ScaleX;
		double xStep = 0.5;
	}
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &memDc, 0, 0, SRCCOPY);

	memDc.SelectObject(pOldBmp);
}

void CArtist::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	bRedraw = true;
}

void CArtist::SetRedrawFlag(bool flag)
{
	bRedraw = flag;
}
