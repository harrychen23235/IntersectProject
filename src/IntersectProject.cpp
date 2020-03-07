// IntersectProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include<unordered_set>
#include<math.h>
using namespace std;
const double EPS = 1e-6;

class Point {
public:double x, y;
      Point(double input1, double input2) {
          x = input1;
          y = input2;
      }

};

struct Hash_Point {
    size_t operator()(const class Point& input1)const {
        return (int)(((int)input1.x) * 1e6 / 10 + ((int)input1.y) * 1e6 / 10);
    }
};

struct Equal_Point {
    bool operator()(const class Point& input1, const class Point& input2)const {
        return abs(input1.x - input2.x) <= EPS && abs(input1.y - input2.y) <= EPS;
    }
};

class Shape {
public:string mtype;
      Shape(string i_type) {
          mtype = i_type;
      }
};
class Line :public Shape{
public:double ma, mb;
    int mspecial;//常规直线mspecial=0,垂直于X轴的直线mspecial=1,ma为X轴对应值
      Line() :Shape("L") {
          ma = 0;
          mb = 0;
          mspecial = 0;
      }
      Line(double i_a, double i_b,int ifspecial) :Shape("L") {
          ma = i_a;
          mb = i_b;
          mspecial = ifspecial;

     }
};
class ShapeFactory {
public:static Shape* GetShape(string type) {
    if (type == "L") {
        double temp1, temp2, temp3, temp4;
        cin >> temp1;
        cin >> temp2;
        cin >> temp3;
        cin >> temp4;
        if (temp1 == temp3) return new Line(temp1, 0, 1);
        else return new Line((temp4-temp2)/(temp3-temp1),temp2- (temp4 - temp2) / (temp3 - temp1)*temp1,0);
    }
    return NULL;

}
};
vector <Shape*> g_allshape;
unordered_set<Point, Hash_Point, Equal_Point> g_allpoint;
void InputProcess() {
    int linenumber;
    cin >> linenumber;
   
    for (int i = 0; i < linenumber; i++) {
        string type;
        cin >> type;
        g_allshape.push_back((Line*)ShapeFactory::GetShape(type));
    }
}
void L2L(Line *input1,Line*input2) {
    if (abs(input1->ma - input2->ma) <= EPS) {
        return;
    }
    if (input1->mspecial == 0 && input2->mspecial == 0) {
        double x = (input2->mb - input1->mb) / (input1->ma - input2->ma);
        double y = x * input1->ma + input1->mb;
        g_allpoint.insert(Point(x, y));
        return;
    }
    else if (input1->mspecial == 1 && input2->mspecial == 1) return;
    else {
        if (input1->mspecial == 1) {
            g_allpoint.insert(Point(input1->ma, input1->ma*input2->ma+input2->mb));
        }
        else {
            g_allpoint.insert(Point(input2->ma, input1->ma * input2->ma + input1->mb));
        }
    }
}
void GetPoint() {
    for (unsigned int i = 0; i < g_allshape.size(); i++) {
        for (unsigned int j = i; j < g_allshape.size(); j++) {
            if (g_allshape.at(i)->mtype== "L" && g_allshape.at(j)->mtype == "L") {

                L2L((Line*)g_allshape.at(i), (Line*)g_allshape.at(j));
            }
            else {

            }
        }
    }
}
int main()
{
    InputProcess();//所有的输入操作处理
    GetPoint();
    cout << g_allpoint.size()<< endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
