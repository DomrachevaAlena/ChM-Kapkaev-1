#include <iostream>
#include <vector>
#include <math.h>
#include <string>

#include "TestTask.hpp"
#include "TaskOne.hpp"
#include "TaskTwo.hpp"

using namespace std;

//Я местами a и b поменял, нужно приветси вход в соответсвие с изменениями
void uiRelise()
{
    setlocale(LC_ALL, "Russian");

    char choise,type;

    double a, b, h, eps, u0,N,u1,epsGr,constant;

    cout << endl;
    cout << "Выбирите задачу:\n";
    cout << "0 - Тестовая задача;\n";
    cout << "1 - Первая задача;\n";
    cout << "2 - Вторая задача;\n";

    cin >> choise;

    cout << endl;
    cout << "Выбирите тип шага:\n";
    cout << "0 - Постоянный;\n";
    cout << "1 - Переменный;\n";

    cin >> type;

    switch (type)
    {
    case('0'):
        switch (choise)
        {
        case('0'):
            cout << "Введите a"<<endl;
            cin >> a;
            cout << endl <<"Введите b" << endl;
            cin >> b;
            cout << endl << "Введите u0" << endl;
            cin >> u0;
            cout << endl << "Введите число шагов" << endl;
            cin >> N;

            cout << endl;

            testTask(a,u0,N,b);
            break;
        case('1'):
            cout << "Введите a" << endl;
            cin >> a;
            cout << endl << "Введите b" << endl;
            cin >> b;
            cout << endl << "Введите u0" << endl;
            cin >> u0;
            cout << endl << "Введите число шагов" << endl;
            cin >> N;

            cout << endl;

           taskOne(a, u0, N, b);
            break;
        case('2'):
            cout << "Введите a" << endl;
            cin >> a;
            cout << endl << "Введите b" << endl;
            cin >> b;
            cout << endl << "Введите u01" << endl;
            cin >> u0;
            cout << endl << "Введите u02" << endl;
            cin >> u1;
            cout << endl << "Введите число шагов" << endl;
            cin >> N;
            cout << endl << "Введите параметр" << endl;
            cin >> constant;

            cout << endl;

            taskTwo(a, { u0 ,u1}, N, b,constant);
            break;
        default:
            cout << "Такого пункта нет :/";
            break;
        }
        break;
    case('1'):
        switch (choise)
        {
        case('0'):
            cout << "Введите a" << endl;
            cin >> a;
            cout << endl << "Введите b" << endl;
            cin >> b;
            cout << endl << "Введите начальный шаг" << endl;
            cin >> h;
            cout << endl << "Введите u0" << endl;
            cin >> u0;
            cout << endl << "Введите eps" << endl;
            cin >> eps;
            cout << endl << "Введите eps граничное" << endl;
            cin >> epsGr;
            cout << endl;

            testTask(a, u0, h, b,eps,epsGr);
            break;
        case('1'):
            cout << "Введите a" << endl;
            cin >> a;
            cout << endl << "Введите b" << endl;
            cin >> b;
            cout << endl << "Введите начальный шаг" << endl;
            cin >> h;
            cout << endl << "Введите u0" << endl;
            cin >> u0;
            cout << endl << "Введите eps" << endl;
            cin >> eps;
            cout << endl << "Введите eps граничное" << endl;
            cin >> epsGr;
            cout << endl;

            cout << endl;

            taskOne(a, u0, h, b, eps, epsGr);
            break;
        case('2'):
            cout << "Введите a" << endl;
            cin >> a;
            cout << endl << "Введите b" << endl;
            cin >> b;
            cout << endl << "Введите начальный шаг" << endl;
            cin >> h;
            cout << endl << "Введите u01" << endl;
            cin >> u0;
            cout << endl << "Введите u02" << endl;
            cin >> u1;
            cout << endl << "Введите eps" << endl;
            cin >> eps;
            cout << endl << "Введите eps граничное" << endl;
            cin >> epsGr;
            cout << endl;
            cout << endl << "Введите параметр" << endl;
            cin >> constant;
            cout << endl;

            taskTwo(a, { u0 ,u1 }, h, b, eps, epsGr,constant);
            break;
        default:
            cout << "Такого пункта нет :/";
            break;
        }
        break;
    default:
        cout << "Такого пункта нет :/";
        break;
    }
}

void uiTest()
{
    taskTwo(-2, { 2 ,8 }, 1000, 8, 1/6);
    //taskOne(1.8, 1, 100, 3.00);
}


int main()
{
    uiTest();


}
