#pragma once
#ifndef INTERSECT_H
#define INTERSECT_H
#include <iostream>
#include <vector>
#include<unordered_set>
#include<math.h>
#include <ctime>
#include<fstream>
#include"shape.h"
using namespace std;
void InputProcess(vector <Shape*>& g_allshape) {
    long long linenumber = 0;
    //cin >> linenumber;
    for (int i = 0; i < linenumber; i++) {
        string type;
        cin >> type;
        g_allshape.emplace_back((Line*)ShapeFactory::GetShape(type));
    }
}
void L2L(Line* input1, Line* input2, unordered_set<Point, Hash_Point, Equal_Point>& g_allpoint) {
    if (input1->mspecial == 0 && input2->mspecial == 0) {
        if (abs(input1->ma - input2->ma) <= EPS) {
            return;
        }
        double x = (input2->mb - input1->mb) / (input1->ma - input2->ma);
        double y = x * input1->ma + input1->mb;
        g_allpoint.insert(Point(x, y));
        return;
    }
    else if (input1->mspecial == 1 && input2->mspecial == 1) return;
    else {
        if (input1->mspecial == 1) {
            g_allpoint.insert(Point(input1->ma, input1->ma * input2->ma + input2->mb));
        }
        else {
            g_allpoint.insert(Point(input2->ma, input1->ma * input2->ma + input1->mb));
        }
    }
}
void C2C(Circle* input1, Circle* input2, unordered_set<Point, Hash_Point, Equal_Point>& g_allpoint) {
    double r2 = input2->mr, r1 = input1->mr, a1 = input1->mx, a2 = input2->mx, b1 = input1->my, b2 = input2->my;
    double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    if (abs(a1 - a2) < EPS && abs(b1 - b2) < EPS) return;
    else if (!Circle::C2DisJudge(input1, input2)) return;
    else if (abs(b1 - b2) < EPS) {
        x1 = (r2 * r2 - r1 * r1 + a1 * a1 - a2 * a2) / (2 * a1 - 2 * a2);
        y1 = sqrt(r1 * r1 - (x1 - a1) * (x1 - a1)) + b1;
        y2 = -sqrt(r1 * r1 - (x1 - a1) * (x1 - a1)) + b1;
        g_allpoint.insert(Point(x1, y1));
        g_allpoint.insert(Point(x1, y2));
        printf("%f %f\n", x1, y1);
        printf("%f %f\n", x1, y2);
        return;
    }
    else {
        double tempm = (r2 * r2 - r1 * r1 + a1 * a1 - a2 * a2 + b1 * b1 - b2 * b2) / (2 * b1 - 2 * b2);
        double tempk = -(2 * a1 - 2 * a2) / (2 * b1 - 2 * b2);
        double temp1 = (1 + tempk * tempk);
        double temp2 = 2 * tempk * (tempm - b1) - 2 * a1;
        double temp3 = a1 * a1 + (tempm - b1) * (tempm - b1) - r1 * r1;
        x1 = (-temp2 + sqrt(temp2 * temp2 - 4 * temp1 * temp3)) / (2 * temp1);
        x2 = (-temp2 - sqrt(temp2 * temp2 - 4 * temp1 * temp3)) / (2 * temp1);
        y1 = tempk * x1 + tempm;
        y2 = tempk * x2 + tempm;
        g_allpoint.insert(Point(x1, y1));
        g_allpoint.insert(Point(x2, y2));
        printf("%f %f\n", x1, y1);
        printf("%f %f\n", x2, y2);
    }
    return;
}
void C2L(Circle* input1, Line* input2, unordered_set<Point, Hash_Point, Equal_Point>& g_allpoint) {
    if (!Circle::CLDisJudge(input1, input2)) return;
    double x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    double  r1 = input1->mr, a1 = input1->mx, b1 = input1->my;
    if (input2->mspecial == 1) {
        x1 = input2->ma;
        y1 = sqrt(r1 * r1 - (x1 - a1) * (x1 - a1)) + b1;
        y2 = -sqrt(r1 * r1 - (x1 - a1) * (x1 - a1)) + b1;
        g_allpoint.insert(Point(x1, y1));
        g_allpoint.insert(Point(x1, y2));
        printf("%f %f\n", x1, y1);
        printf("%f %f\n", x1, y2);
        return;
    }
    else {
        double tempm = input2->mb;
        double tempk = input2->ma;
        double temp1 = (1 + tempk * tempk);
        double temp2 = 2 * tempk * (tempm - b1) - 2 * a1;
        double temp3 = a1 * a1 + (tempm - b1) * (tempm - b1) - r1 * r1;
        x1 = (-temp2 + sqrt(temp2 * temp2 - 4 * temp1 * temp3)) / (2 * temp1);
        x2 = (-temp2 - sqrt(temp2 * temp2 - 4 * temp1 * temp3)) / (2 * temp1);
        y1 = tempk * x1 + tempm;
        y2 = tempk * x2 + tempm;
        g_allpoint.insert(Point(x1, y1));
        g_allpoint.insert(Point(x2, y2));
        printf("%f %f\n", x1, y1);
        printf("%f %f\n", x2, y2);
    }
}
 void GetPoint(vector <Shape*>& g_allshape, unordered_set<Point, Hash_Point, Equal_Point>& g_allpoint) {
    for (unsigned int i = 0; i < g_allshape.size(); i++) {
        cout << i << endl;
        for (unsigned int j = i + 1; j < g_allshape.size(); j++) {
            if (g_allshape.at(i)->mtype == "L" && g_allshape.at(j)->mtype == "L") {
                L2L((Line*)g_allshape.at(i), (Line*)g_allshape.at(j), g_allpoint);
            }
            else if (g_allshape.at(i)->mtype == "C" && g_allshape.at(j)->mtype == "C") {
                C2C((Circle*)g_allshape.at(i), (Circle*)g_allshape.at(j), g_allpoint);
            }
            else if (g_allshape.at(i)->mtype == "C" && g_allshape.at(j)->mtype == "L") {
                C2L((Circle*)g_allshape.at(i), (Line*)g_allshape.at(j), g_allpoint);
            }
            else if (g_allshape.at(i)->mtype == "L" && g_allshape.at(j)->mtype == "C") {
                C2L((Circle*)g_allshape.at(j), (Line*)g_allshape.at(i), g_allpoint);
            }
        }
    }
}

#endif // !INTERSECT_H

