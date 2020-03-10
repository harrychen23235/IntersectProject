// IntersectProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include<unordered_set>
#include<math.h>
#include <ctime>
#include <fstream>
#include"shape.h"
#include"intersect.h"
using namespace std;
int main(int argc,char*argv[])
{
	FILE* stream1;
	FILE* stream2;
	for (int arg = 0; arg < argc; arg++) {
		if ((string)argv[arg] == "-i") {
			freopen_s(&stream1,argv[arg + 1], "r", stdin);
		}
		else if ((string)argv[arg] == "-o") {
			freopen_s(&stream2,argv[arg + 1], "w", stdout);
		}
	}
	//freopen_s(&stream1, "G:\\360MoveData\\Users\\HP\\Desktop\\IntersectProject\\Debug\\test.txt", "r", stdin);
    vector <Shape*> g_allshape;
    unordered_set<Point*, Hash_Point, Equal_Point> g_allpoint;
    InputProcess(g_allshape);//所有的输入操作处理
    GetPoint(g_allshape, g_allpoint);//得到最终节点
    cout << g_allpoint.size()<< endl;
    fclose(stdin);
    return 0;
}


