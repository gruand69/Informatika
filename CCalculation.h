#pragma once
class CCalculation
{
public:
	double GetY(double x, const Parameters& params);
	double GetLinearY(double x, const Parameters& params);
	double GetDifference(double x, const Parameters& params);
	double FindRoot(double left, double right, const Parameters& params, double epsilon, int& iterations);
};

