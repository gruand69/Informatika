#include "pch.h"
#include "CTrans.h"
#define _USE_MATH_DEFINES
#include <math.h>


CTrans::CTrans() :
	m_ScaleX(0),
	m_ScaleY(0),
	m_center(0, 0)
{

}

CTrans::~CTrans()
{

}


void CTrans::SetTransParam(int Xwidth, int Yheight)
{
	m_ScaleX = (double)(Xwidth - 2 * BORDER_W) / (2.0 * M_PI);
	m_ScaleY = (double)(Yheight - 2 * BORDER_W) / 8.;
	m_center.x = Xwidth / 2;
	m_center.y = Yheight / 2;

}

CPoint CTrans::GetPoint(double X, const Parameters& params)
{
	CPoint Cur = Trans(X, params);
	return Cur;
}

CPoint CTrans::Trans(double x, const Parameters& params)
{
	double y = 0.0;

	if (params.d == 0.0 && params.e == 0.0)
		y = GetY(x, params);
	else
		y = GetLinearY(x, params);

	int screenX = static_cast<int>(m_center.x + x * m_ScaleX);
	int screenY = static_cast<int>(m_center.y - y * m_ScaleY);

	return CPoint(screenX, screenY);
}

double CTrans::ScreenToMathX(int screenX)
{
	return (screenX - m_center.x) / m_ScaleX;
}
