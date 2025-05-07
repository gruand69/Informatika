#include "pch.h"
#include "CCalculation.h"
#include <cmath>

double CCalculation::GetY(double x, const Parameters& params)
{
    double y1 = params.a * sin(params.b * x + params.c);
    return y1;
}

double CCalculation::GetLinearY(double x, const Parameters& params)
{
    double y2 = params.d * x + params.e;
    return y2;
}

double CCalculation::GetDifference(double x, const Parameters& params)
{
    double y1 = GetY(x, params);
    double y2 = GetLinearY(x, params);
    return y1 - y2;
}

double CCalculation::FindRoot(double left, double right, const Parameters& params, double epsilon, int& iterations)
{
    double mid = 0.0;
    iterations = 0;
    const int MAX_ITERATIONS = 1000;

    while ((right - left) / 2.0 > epsilon && iterations < MAX_ITERATIONS)
    {
        mid = (left + right) / 2.0;
        if (fabs(GetDifference(mid, params)) < epsilon)
            return mid;
        if (GetDifference(left, params) * GetDifference(mid, params) < 0)
            right = mid;
        else
            left = mid;
        iterations++;
    }
    return mid;
}
