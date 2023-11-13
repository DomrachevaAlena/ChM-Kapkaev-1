#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <math.h>

#include "Table.hpp"

#define MAX_ITER 10000

using namespace std;

vector<double> rk4Step(const vector<double(*)(double x, const vector<double>& v, const vector<double>& consts)> &f, double x,const vector<double> &v, const vector<double> &consts, double h)
{
	vector<double> k1, k2, k3, k4, res;
	vector<double> currentV(v.size());

	for (int i = 0; i < f.size(); i++)
		k1.push_back(f[i](x, v, consts));

	for (int i = 0; i < v.size(); i++)
		currentV[i] = v[i]+ (h * k1[i]) / 2.0;

	for (int i = 0; i < f.size(); i++)
		k2.push_back(f[i](x+h/2.0,currentV, consts));

	for (int i = 0; i < v.size(); i++)
		currentV[i] = v[i] + (h * k2[i]) / 2.0;

	for (int i = 0; i < f.size(); i++)
		k3.push_back(f[i](x+h/2.0, currentV, consts));

	for (int i = 0; i < v.size(); i++)
		currentV[i] = v[i] + h * k3[i];

	for (int i = 0; i < f.size(); i++)
		k4.push_back(f[i](x+h, currentV, consts));

	for (int i = 0; i < f.size(); i++)
		res.push_back(v[i] + h / 6.0 * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]));

	return res;
}

MyTable* rk4ConstStep(const vector<double(*)(double x, const vector<double>& v, const vector<double>& consts)> &f, double x0,const vector<double> &v,const vector<double> &consts, double N, double xLast)
{
	MyTable* table = new MyTable(v.size());

	size_t iter = 0;
	double xi = x0;
	vector<double> tmp;
	vector<double> vi = v;
	vector<double> v2i = v;

	double h = (xLast - x0) / N;

	table->addRow(xi, vi, v2i, h, 0.0, 0.0);

	for (int i = 1; i <= N && i < MAX_ITER; i++)
	{
		tmp = rk4Step(f, xi, vi, consts, h / 2.0);
		v2i = rk4Step(f, xi+h/2.0, tmp, consts, h / 2.0);

		vi = rk4Step(f, xi, vi, consts, h);

		xi = x0 + (xLast - x0) / N * i;

		table->addRow(xi, vi, v2i, h, 0.0, 0.0);
	}

	return table;
}

MyTable* rk4VariableStep(const vector<double(*)(double x, const vector<double>& v, const vector<double>& consts)> &f, double x0, const vector<double>& v, const vector<double>& consts, double h, double xLast, double eps,double epsGr)
{
	MyTable* table = new MyTable(v.size());

	size_t iter = 0;
	double xi = x0, maxS = 0.0, C1 = 0.0, C2 = 0.0;
	vector<double> vi = v;
	vector<double> v2i = vi;
	vector<double> viPrev;
	vector<double> S;

	table->addRow(xi, vi, v2i, h, 0.0, 0.0);

	while ((xi+h) <= xLast && iter<MAX_ITER)
	{
		v2i = rk4Step(f, xi, vi, consts, h / 2.0);
		v2i = rk4Step(f, xi + h / 2.0, v2i, consts, h / 2.0);

		viPrev = vi;
		vi = rk4Step(f, xi, vi, consts, h);

		for (int i = 0; i < vi.size(); i++)
			S.push_back((vi[i] - v2i[i]) / 15.0);

		for (int i = 0; i < S.size(); i++)
			if (maxS < abs(S[i]))
				maxS = abs(S[i]);

		if (maxS < eps / 32.0)
		{
			xi = xi + h;
			h = h * 2.0;

			C2 += 1.0;

			table->addRow(xi, vi, v2i, h, C1, C2);
		}
		else if (maxS > eps)
		{
			h = h / 2.0;
			C1 += 1.0;

			vi = viPrev;
		}
		else
		{
			xi = xi + h;
			table->addRow(xi, vi, v2i, h, C1, C2);
		}

		maxS = 0.0;
		S.clear();
	}

	if (xi < (xLast - epsGr))
	{
		double h1 = (xLast - xi) / 2.0;

		while (xi < xLast-epsGr || maxS > eps)
		{
			v2i = rk4Step(f, xi, vi, consts, h1 / 2.0);
			v2i = rk4Step(f, xi + h1 / 2.0, v2i, consts, h1 / 2.0);

			viPrev = vi;
			vi = rk4Step(f, xi, vi, consts, h1);

			for (int i = 0; i < vi.size(); i++)
				S.push_back((vi[i] - v2i[i]) / 15.0);

			for (int i = 0; i < S.size(); i++)
				if (maxS < abs(S[i]))
					maxS = abs(S[i]);

			S.clear();

			if (maxS > eps)
			{
				h1 = h1 / 2.0;
				vi = viPrev;
			}
			else if(xi < xLast - epsGr)
			{
				xi = xi + h1;
				table->addRow(xi, vi, v2i, h1, C1, C2);
			}
		}
	}

	return table;
}
