#pragma once
#include <afxwin.h>
//#include "pch.h"
#include "Idata.h"
#include "CCalculation.h"
#include "CTrans.h"



class CArtist :
    public CStatic
{
    public:
        CArtist();
       virtual ~CArtist();
    protected:
        COLORREF m_bkCol;
        COLORREF m_AxisColor;
        COLORREF m_SinColor;
        COLORREF m_LinearColor;
        Idata* m_Idata = nullptr;
        bool bRedraw = true; // ‘лаг перерисовки
        CDC* m_MemDc = nullptr; // ”казатель на контекст устройства пам€ти
        CBitmap* m_BitMap = nullptr; // ”казатель на растровое изображение
        int m_NumDigits; // „исло знаков после зап€той
    public:
        void SetParams(Parameters* params);
        void SetBkColor(COLORREF col) { m_bkCol = col; }
        void SetAxisColor(COLORREF col) { m_AxisColor = col; }
        void SetSinColor(COLORREF col) { m_SinColor = col; }
        void SetLinearColor(COLORREF col) { m_LinearColor = col; }
        void SetIdataPtr(Idata* pData) { m_Idata = pData; }
        void SetCalculation(CCalculation* calc, Parameters* params, CTrans* trans);
        DECLARE_MESSAGE_MAP()
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        //void SetPrecision(int precision) { m_NumDigits = precision; }
        void SetRedraw() { bRedraw = true; }
        int GetPrecision () const { return m_NumDigits; }
    private:
        CCalculation* m_Calculation;
        CTrans* m_Trans;
        Parameters* m_params;

    public:
        afx_msg void OnPaint();
        afx_msg void OnSize(UINT nType, int cx, int cy);
        void SetRedrawFlag(bool flag);
        void SetPrecision(int precision);
};

