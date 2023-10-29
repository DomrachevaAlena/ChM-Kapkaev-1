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
	double k1, k2, k3, k4;
	vector<double> res;
	vector<double> tmp(v.size());

	for (int i = 0; i < f.size(); i++)
	{
		k1 = f[i](x, v,consts);

		for (int j = 0; j < v.size(); j++)
			tmp[i] = v[i] + (h * k1) / 2.0;

		k2 = f[i](x + h / 2.0, tmp, consts);

		for (int j = 0; j < v.size(); j++)
			tmp[i] = v[i] + (h * k2) / 2.0;

		k3 = f[i](x + h / 2.0, tmp, consts);

		for (int j = 0; j < v.size(); j++)
			tmp[i] = v[i] + h * k3;

		k4 = f[i](x + h, tmp, consts);

		res.push_back(v[i] + (h * (k1 + 2.0 * k2 + 2.0 * k3 + k4)) / 6.0);
	}

	return res;
}

Table* rk4ConstStep(const vector<double(*)(double x, const vector<double>& v, const vector<double>& consts)> &f, double x0,const vector<double> &v,const vector<double> &consts, double h, double xLast)
{
	Table* table = new Table(v.size());

	size_t iter = 0;
	double xi = x0;
	vector<double> tmp;
	vector<double> vi = v;
	vector<double> v2i = v;

	table->addRow(xi, vi, v2i, h, 0.0, 0.0);

	while (xi <= xLast && iter < MAX_ITER)
	{
		xi = xi + h;

		tmp = rk4Step(f, xi, vi,consts, h / 2.0);
		v2i = rk4Step(f, xi, tmp,consts, h / 2.0);

		vi = rk4Step(f, xi, vi, consts, h);

		table->addRow(xi, vi, v2i, h, 0.0, 0.0);
	}

	table->printTable();

	return table;
}

Table* rk4VariableStep(const vector<double(*)(double x, const vector<double>& v, const vector<double>& consts)> &f, double x0, const vector<double>& v, const vector<double>& consts, double h, double xLast, double eps)
{
	Table* table = new Table(v.size());

	size_t iter = 0;
	double xi = x0, maxS = 0.0, C1 = 0.0, C2 = 0.0;
	vector<double> vi = v;
	vector<double> v2i = vi;
	vector<double> viPrev;
	vector<double> S;

	table->addRow(xi, vi, v2i, h, 0.0, 0.0);

	while (xi <= xLast && iter<MAX_ITER)
	{
		v2i = rk4Step(f, xi + h / 2.0, vi, consts, h / 2.0);
		v2i = rk4Step(f, xi + h / 2.0, v2i, consts, h / 2.0);

		viPrev = vi;
		vi = rk4Step(f, xi + h, vi, consts, h);

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

	table->printTable();

	return table;
}