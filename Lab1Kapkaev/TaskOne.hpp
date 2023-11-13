#pragma once
#include "Table.hpp"
#include "RK4.hpp"
#include "PrintSpravka.hpp"

double firstTuskFunction(double x, const vector<double>& u, const vector<double>& consts) { return u[0] * u[0] / (2 * x + x * x) + u[0] - u[0] * u[0] * u[0] * sin(10.0 * x); }

void showRes(MyTable* res,double b)
{
	vector<double> Xi = res->getColumn("Xi");
	vector<double> Vi = res->getColumn("Vi");

#ifdef _DEBUG 
	res->printTable();
#else
	res->saveToTXT();
	spravka(res, b);

	plt::suptitle("Task one");
	plt::xlabel("X");
	plt::ylabel("V / U");
	plt::plot(Xi, Vi, { {"color", "red"}});
	plt::show();
#endif
}

//С постоянным шагом
void taskOne(double x0, double u0, double N, double xLast)
{
	MyTable* res = rk4ConstStep({ &firstTuskFunction }, x0, { u0 }, {}, N, xLast);

	showRes(res,xLast);
}

//С переменным шагом
void taskOne(double x0, double u0, double h, double xLast, double eps,double epsGr)
{
	MyTable* res = rk4VariableStep({ &firstTuskFunction }, x0, { u0 }, {}, h, xLast, eps, epsGr);
	
	showRes(res,xLast);
}

