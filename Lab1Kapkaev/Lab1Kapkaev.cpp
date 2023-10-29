// Lab1Kapkaev.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include "TestTask.hpp"
#include "TaskOne.hpp"
#include "TaskTwo.hpp"

using namespace std;

double secondFunction(double x, double u)
{
    return 0;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    char choise;

    double a, b, h,eps,u0;

    cout << "Введите a"<<endl;
    cin >> a;
    cout << "Введите b" << endl;
    cin >> b;
    cout << "Введите h" << endl;
    cin >> h;
    cout << "Введите eps" << endl;
    cin >> eps;

    cout << endl;
    cout << "Выбирите задачу:\n";
    cout << "0 - Тестовая задача;\n";
    cout << "1 - Первая задача;\n";
    cout << "2 - Вторая задача;\n";

    cin >> choise;

    cout << endl;
    switch (choise)
    {
    case('0'):
        cout << "Введите u0" << endl;
        cin >> u0;

        cout << endl;
        cout << "---------------------------ПОСТОЯННЫЙ ШАГ---------------------------" << endl;
        cout << endl;
        testTask(a, b, h, b);

        cout << endl;
        cout << "---------------------------ПЕРЕМЕННЫЙ ШАГ---------------------------" << endl;
        cout << endl;
        testTask(a,1,h,b,eps);
        break;
    case('1'):
        cout << "Введите u0" << endl;
        cin >> u0;

        cout << endl;
        cout << "---------------------------ПОСТОЯННЫЙ ШАГ---------------------------" << endl;
        cout << endl;
        taskOne(a, b, h, b);

        cout << endl;
        cout << "---------------------------ПЕРЕМЕННЫЙ ШАГ---------------------------" << endl;
        cout << endl;
        taskOne(a, 1, h, b, eps);
        break;
    case('2'):
        double u01, u02;
        cout << "Введите u01" << endl;
        cin >> u01;

        cout << "Введите u01" << endl;
        cin >> u02;

        cout << endl;
        cout << "---------------------------ПОСТОЯННЫЙ ШАГ---------------------------" << endl;
        cout << endl;
        taskTwo(a, { u01, u02 }, h, b, eps);

        cout << endl;
        cout << "---------------------------ПЕРЕМЕННЫЙ ШАГ---------------------------" << endl;
        cout << endl;
        taskTwo(a, {u01, u02}, h, b, eps);
        break;
    default:
        cout << "Такого пункта нет :/";
        break;
    }
}
