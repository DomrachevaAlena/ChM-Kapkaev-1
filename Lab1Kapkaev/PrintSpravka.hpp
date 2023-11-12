#pragma once

#include "Table.hpp"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

void spravka(MyTable* res, double b)
{
    setlocale(LC_ALL, "Russian");

    size_t size = res->getColumn("Xi").size(), maxHind = 0, minHind = 0;
    double maxOLP = -1.0, maxH = res->getColumn("h")[0], minH = res->getColumn("h")[0];
    cout << "n = " << size << ", b-xn = " << b - res->getColumn("Xi")[size-1] << endl;

    vector<double> OLP = res->getColumn("OLP");
    vector<double> h = res->getColumn("h");

    for (int i = 0; i < size; i++)
        if (maxOLP < abs(OLP[i]))
            maxOLP = abs(OLP[i]);

    cout << "max|OLP| = " << maxOLP << endl;

    for (int i = 1; i < size; i++)
    {
        if (maxH < h[i])
        {
            maxH = h[i];
            maxHind = i;
        }

        if (minH > h[i])
        {
            minH = h[i];
            minHind = i;
        }
    }

    cout << "max h = " << maxH << " при x = " << res->getColumn("Xi")[maxHind] << endl;
    cout << "min h = " << minH << " при x = " << res->getColumn("Xi")[minHind] << endl;
}
