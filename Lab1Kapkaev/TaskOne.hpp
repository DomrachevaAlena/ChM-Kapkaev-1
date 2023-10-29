#pragma once
#include "RK4.hpp"

#include "TestTask.hpp"
#include "Table.hpp"
#include "RK4.hpp"

double firstTuskFunction(double x, const vector<double>& u, const vector<double>& consts) { return u[0] * u[0] / (2 * x + x * x) + u[0] - u[0] * u[0] * u[0] * sin(10.0 * x); }

//С постоянным шагом
void taskOne(double x0, double u0, double h, double xLast)
{
	rk4ConstStep({ &firstTuskFunction }, x0, { u0 }, {}, h, xLast);
}

//С переменным шагом
void taskOne(double x0, double u0, double h, double xLast, double eps)
{
	rk4VariableStep({ &firstTuskFunction }, x0, { u0 }, {}, h, xLast, eps);
}

