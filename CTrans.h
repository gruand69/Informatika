#pragma once
#include "CCalculation.h"
class CTrans :
    public CCalculation
{
public:
    CTrans();
    ~CTrans();
    double m_ScaleX;
    double m_ScaleY;
    CPoint m_center;
    void SetTransParam(int Xwidth, int Yheight);
    CPoint GetPoint(double X, const Parameters& params);
    CPoint Trans(double x, const Parameters& params);
    double ScreenToMathX(int screenX);
};

