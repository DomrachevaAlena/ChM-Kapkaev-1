#pragma once
#include "Table.hpp"
#include "RK4.hpp"
#include "PrintSpravka.hpp"

#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

double testFunction(double x, const vector<double> &u,const vector<double> &consts) { return 3.0 * u[0]; }

void showRes(MyTable* res,double u0,double b)
{
	vector<double> real;
	vector<double> difference;
	vector<double> Xi = res->getColumn("Xi");
	vector<double> Vi = res->getColumn("Vi");

	for (int i = 0; i < Xi.size(); i++)
	{
		real.push_back(u0 * exp(3 * Xi[i]));
		difference.push_back(abs(u0 * exp(3 * Xi[i]) - Vi[i]));
	}

	res->addColumn("Ui", real);
	res->addColumn("|Ui-Vi|", difference);

#ifdef _DEBUG 
	res->printTable();
#else
	res->saveToTXT();
	spravka(res,b);

	int maxDifInd = 0;
	double maxDiff = 0;
	for (int i=0; i < difference.size(); i++)
	{
		if (difference[i] > maxDiff)
		{
			maxDiff = difference[i];
			maxDifInd = i;
		}
	}

	cout << "max|Ui-Vi| = " << maxDiff << " x = " << Xi[maxDifInd];

	plt::suptitle("Test task");
	plt::xlabel("X");
	plt::ylabel("V / U");
	plt::plot(Xi, Vi, { {"color", "red"}, { "linestyle", "--" } });
	plt::plot(Xi, real, { {"color", "blue"}, { "linestyle", ":" } });
	plt::show();
#endif
}

//С постоянным шагом
void testTask(double x0, double u0, double N, double xLast)
{
	MyTable* res = rk4ConstStep({ &testFunction }, x0, { u0 }, {}, N, xLast);

	showRes(res, u0,xLast);
}

//С переменным шагом
void testTask(double x0, double u0, double h, double xLast, double eps,double epsGr)
{
	MyTable* res = rk4VariableStep({ &testFunction }, x0, { u0 }, {}, h, xLast, eps,epsGr);
	
	showRes(res, u0, xLast);
}
