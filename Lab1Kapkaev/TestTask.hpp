#pragma once
#include "RK4.hpp"

#include "TestTask.hpp"
#include "Table.hpp"
#include "RK4.hpp"

double testFunction(double x, const vector<double> &u,const vector<double> &consts) { return 3.0 * u[0]; }

//С постоянным шагом
void testTask(double x0, double u0, double h, double xLast)
{
	//Добавить вывод Ui и |Ui-Vi|
	rk4ConstStep({ &testFunction }, x0, { u0 }, {}, h, xLast);
}

//С переменным шагом
void testTask(double x0, double u0, double h, double xLast, double eps)
{
	//Добавить вывод Ui и |Ui-Vi|
	rk4VariableStep({ &testFunction }, x0, { u0 }, {}, h, xLast, eps);
}
