#pragma once
#include "TaskTwo.hpp"
#include "Table.hpp"
#include "RK4.hpp"

double taskTwoFunction1(double x, const vector<double>& u, const vector<double>& consts) { return u[0]; }
double taskTwoFunction2(double x, const vector<double>& u, const vector<double>& consts) { return (-1.0)*consts[0]*sqrt(u[1]*u[1]+1); }

//С постоянным шагом
void taskTwo(double x0, vector<double> u, double h, double xLast)
{
	rk4ConstStep({ &taskTwoFunction1,&taskTwoFunction2 }, x0,u,{x0}, h, xLast);
}

//С переменным шагом
void taskTwo(double x0, vector<double> u, double h, double xLast, double eps)
{
	rk4VariableStep({ &taskTwoFunction1,&taskTwoFunction2 }, x0, u, { x0 }, h, xLast, eps);
}