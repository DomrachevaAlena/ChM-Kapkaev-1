#pragma once
#include "TaskTwo.hpp"
#include "Table.hpp"
#include "RK4.hpp"

double taskTwoFunction1(double x, const vector<double>& u, const vector<double>& consts) { return u[0]; }
double taskTwoFunction2(double x, const vector<double>& u, const vector<double>& consts) { return (-1.0)*consts[0]*sqrt(u[1]*u[1]+1); }

//С постоянным шагом
void taskTwo(double x0, vector<double> u, double N, double xLast)
{
	MyTable* res = rk4ConstStep({ &taskTwoFunction1,&taskTwoFunction2 }, x0,u,{x0},N, xLast);

	vector<double> Xi = res->getColumn("Xi");
	vector<double> Vi1 = res->getColumn("Vi1");
	vector<double> Vi2 = res->getColumn("Vi2");

#ifdef _DEBUG 
	res->printTable();
#else
	res->saveToTXT();

	plt::suptitle("Task two");
	plt::plot(Vi1,Vi2);
	plt::show();
#endif
}

//С переменным шагом
void taskTwo(double x0, vector<double> u, double h, double xLast, double eps,double epsGr)
{
	MyTable* res = rk4VariableStep({ &taskTwoFunction1,&taskTwoFunction2 }, x0, u, { x0 }, h, xLast, eps, epsGr);

	vector<double> Xi = res->getColumn("Xi");
	vector<double> Vi1 = res->getColumn("Vi1");
	vector<double> Vi2 = res->getColumn("Vi2");

#ifdef _DEBUG 
	res->printTable();
#else
	res->saveToTXT();

	plt::suptitle("Task two");
	plt::plot(Vi1, Vi2);
	plt::show();
#endif
}
