#pragma once
#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include<math.h>
#include<fstream>
using namespace std;
const double EPS = 1e-6;
class Shape {
public:string mtype;
      Shape(string i_type) {
          mtype = i_type;
      }
};
class Line :public Shape {
public:double ma, mb;
      int mspecial;//常规直线mspecial=0,垂直于X轴的直线mspecial=1,ma为X轴对应值
      Line() :Shape("L") {
          ma = 0;
          mb = 0;
          mspecial = 0;
      }
      Line(double input1, double input2, int ifspecial) :Shape("L") {
          ma = input1;
          mb = input2;
          mspecial = ifspecial;

      }
};
class Circle :public Shape {
public:double mx, my, mr;
      Circle() :Shape("C") {
          mx = 0;
          my = 0;
          mr = 0;
      }
      Circle(double input1, double input2, double input3) :Shape("C") {
          mx = input1;
          my = input2;
          mr = input3;

      }
      static bool C2DisJudge(Circle* input1, Circle* input2) {//圆和圆是否相交
          double distance = (input1->mx - input2->mx) * (input1->mx - input2->mx) + (input1->my - input2->my) * (input1->my - input2->my);
          double radium1 = (input1->mr + input2->mr) * (input1->mr + input2->mr);
          double radium2 = (input1->mr - input2->mr) * (input1->mr - input2->mr);
          return distance - EPS < radium1&&distance+EPS>radium2;
      }
      static bool CLDisJudge(Circle* input1, Line* input2) {//圆和线是否相交
          double A=0, B=0, C=0;
          if (input2->mspecial == 1) {
              A = 1;
              B = 0;
              C = -input2->mb;
          }
          else {
              A = input2->ma;
              B = -1;
              C = input2->mb;
          }
          double temp1 = (A * input1->mx + B * input1->my + C) * (A * input1->mx + B * input1->my + C);
          double temp2 = temp1  / (A * A + B * B);
          return temp2 - EPS < input1->mr * input1->mr;

      }
};
class ShapeFactory {//工厂模式处理
public:static Shape* GetShape(string type) {
    if (type == "L") {
        double temp1, temp2, temp3, temp4;
        cin >> temp1;
        cin >> temp2;
        cin >> temp3;
        cin >> temp4;
        if (temp1 == temp3) return new Line(temp1, 0, 1);
        else return new Line((temp4 - temp2) / (temp3 - temp1), temp2 - (temp4 - temp2) / (temp3 - temp1) * temp1, 0);
    }
    else if (type == "C") {
        double temp1, temp2, temp3;
        cin >> temp1;
        cin >> temp2;
        cin >> temp3;
        return new Circle(temp1, temp2, temp3);
    }
    else {
        throw"UNKNOWN TYPE";
    }
    return NULL;

}
      static Shape* GetShape(string type,double temp1,double temp2,double temp3,double temp4) {
          if (type == "L") {
              if (temp1 == temp3) return new Line(temp1, 0, 1);
              else return new Line((temp4 - temp2) / (temp3 - temp1), temp2 - (temp4 - temp2) / (temp3 - temp1) * temp1, 0);
          }
          else if (type == "C") {
              return new Circle(temp1, temp2, temp3);
          }
          else {
              throw"UNKNOWN TYPE";
          }
          return NULL;

      }
};
class Point {
public:double x, y;
      Point(double input1, double input2) {
          x = input1;
          y = input2;
      }

};

struct Hash_Point {
    size_t operator()(const class Point* input1)const {
        //return (int)(((int)input1.x) * 1e6 / 10 + ((int)input1.y) * 1e6 / 10);
        long temp1 = (long)input1->x;
        long temp2 = (long)input1->y;
        return (temp1 + temp2) * 13 + (temp1 * 1000 % 1000 + temp2 * 1000 % 1000);
    }
};

struct Equal_Point {
    bool operator()(const class Point* input1, const class Point* input2)const {
        return abs(input1->x - input2->x) <= EPS && abs(input1->y - input2->y) <= EPS;
        //return input1.x == input2.x && input1.y == input2.y;
    }
};

#endif 

