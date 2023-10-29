#pragma once
#include "RK4.hpp"

#include "TestTask.hpp"
#include "Table.hpp"
#include "RK4.hpp"

double testFunction(double x, const vector<double> &u,const vector<double> &consts) { return 3.0 * u[0]; }

//� ���������� �����
void testTask(double x0, double u0, double h, double xLast)
{
	//�������� ����� Ui � |Ui-Vi|
	rk4ConstStep({ &testFunction }, x0, { u0 }, {}, h, xLast);
}

//� ���������� �����
void testTask(double x0, double u0, double h, double xLast, double eps)
{
	//�������� ����� Ui � |Ui-Vi|
	rk4VariableStep({ &testFunction }, x0, { u0 }, {}, h, xLast, eps);
}
