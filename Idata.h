#pragma once
#include <vector>


class Idata
{
public:
	Idata();
	virtual ~Idata() = default;
	virtual size_t IGetSinPoints(std::vector<CPoint>& vec) = 0;
	virtual size_t IGetLinearPoints(std::vector<CPoint>& vec) = 0;
};

