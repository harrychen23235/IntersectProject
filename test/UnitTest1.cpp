#include "pch.h"
#include "CppUnitTest.h"
#include"..\IntersectProject\intersect.h"
#include <iostream>
#include <vector>
#include<unordered_set>
#include<math.h>
#include <ctime>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			vector <Shape*> allshape1;
			unordered_set<Point*, Hash_Point, Equal_Point> allpoint1;
			allshape1.emplace_back(ShapeFactory::GetShape("L",1,1,1,1));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 1, 1, 1, 1));
			GetPoint(allshape1, allpoint1);
			Assert::AreEqual(0, (int)allpoint1.size());
		}
		TEST_METHOD(TestMethod2)
		{
			vector <Shape*> allshape1;
			unordered_set<Point*, Hash_Point, Equal_Point> allpoint1;
			allshape1.emplace_back(ShapeFactory::GetShape("L", 0,0,0,1));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 0,0,1,0));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 0, 0, 1, 1));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 0, 1, 1, 1));
			GetPoint(allshape1, allpoint1);
			Assert::AreEqual(3, (int)allpoint1.size());
		}
		TEST_METHOD(TestMethod3)
		{
			vector <Shape*> allshape1;
			unordered_set<Point*, Hash_Point, Equal_Point> allpoint1;
			allshape1.emplace_back(ShapeFactory::GetShape("L", -10, -9, -9, 10));
			allshape1.emplace_back(ShapeFactory::GetShape("L", -9, 10, 10, 9));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 10, 9, 9, -10));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 9, -10, -10, -9));
			GetPoint(allshape1, allpoint1);
			Assert::AreEqual(4, (int)allpoint1.size());
		}
		TEST_METHOD(TestMethod4)
		{
			vector <Shape*> allshape1;
			unordered_set<Point*, Hash_Point, Equal_Point> allpoint1;
			allshape1.emplace_back(ShapeFactory::GetShape("L",-100, -99, -99, 100));
			allshape1.emplace_back(ShapeFactory::GetShape("L",-99, 100, 100, 99));
			allshape1.emplace_back(ShapeFactory::GetShape("L",100, 99, 99, -100));
			allshape1.emplace_back(ShapeFactory::GetShape("L",90, -100, -100, -99));
			GetPoint(allshape1, allpoint1);
			Assert::AreEqual(5, (int)allpoint1.size());
		}
		TEST_METHOD(TestMethod5)
		{
			vector <Shape*> allshape1;
			unordered_set<Point*, Hash_Point, Equal_Point> allpoint1;
			allshape1.emplace_back(ShapeFactory::GetShape("L", -99999, 0, 99999, 1));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 0, 0, 1, 0));
			allshape1.emplace_back(ShapeFactory::GetShape("L", -99998, 0, -99998, 1));
			GetPoint(allshape1, allpoint1);
			Assert::AreEqual(3, (int)allpoint1.size());
		}
		TEST_METHOD(TestMethod6)
		{
			vector <Shape*> allshape1;
			unordered_set<Point*, Hash_Point, Equal_Point> allpoint1;
			allshape1.emplace_back(ShapeFactory::GetShape("L", 0, 0, 99998, 2));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 0, 2, 49999, 3));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 0, 0, -99999, 0));
			GetPoint(allshape1, allpoint1);
			Assert::AreEqual(2, (int)allpoint1.size());
		}
		TEST_METHOD(TestMethod7)
		{
			vector <Shape*> allshape1;
			unordered_set<Point*, Hash_Point, Equal_Point> allpoint1;
			allshape1.emplace_back(ShapeFactory::GetShape("L", 0, 0, 1, 1));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 1, 0, 0, 1));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 1, 2, 2, 0));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 0, 3, 1, 2));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 0, 1, 2, 2));
			GetPoint(allshape1, allpoint1);
			Assert::AreEqual(9, (int)allpoint1.size());
		}
		TEST_METHOD(TestMethod8)
		{
			vector <Shape*> allshape1;
			unordered_set<Point*, Hash_Point, Equal_Point> allpoint1;
			allshape1.emplace_back(ShapeFactory::GetShape("L", 0, 0, 0, 1));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 2, 0, 2, 1));
			allshape1.emplace_back(ShapeFactory::GetShape("C", 1, 0, 1, 0));
			GetPoint(allshape1, allpoint1);
			Assert::AreEqual(2, (int)allpoint1.size());
		}
		TEST_METHOD(TestMethod9)
		{
			vector <Shape*> allshape1;
			unordered_set<Point*, Hash_Point, Equal_Point> allpoint1;
			allshape1.emplace_back(ShapeFactory::GetShape("C", 1 ,0 ,2,0));
			allshape1.emplace_back(ShapeFactory::GetShape("C",2 ,2 ,1,0));
			allshape1.emplace_back(ShapeFactory::GetShape("C", 3 ,-2 ,6,0));
			allshape1.emplace_back(ShapeFactory::GetShape("L", -1, 4 ,4 ,-1));
			GetPoint(allshape1, allpoint1);
			Assert::AreEqual(6, (int)allpoint1.size());
		}
		TEST_METHOD(TestMethod10)
		{
			Circle c1 = Circle(1, 0, 1);
			Circle c2 = Circle(3, 0, 1);
			Circle c3 = Circle(4, 0, 1);
			Circle c4 = Circle(-5, 0, 7);
			Assert::AreEqual(true, Circle::C2DisJudge(&c1, &c2));
			Assert::AreEqual(false, Circle::C2DisJudge(&c1, &c3));
			Assert::AreEqual(true, Circle::C2DisJudge(&c1, &c4));
		}
		TEST_METHOD(TestMethod11)
		{
			Circle c1 = Circle(5, 0, 5);
			Line l1 = Line(0,5,0);
			Line l2 = Line(0, 4, 0);
			Line l3 = Line(0, 6, 0);
			Assert::AreEqual(true, Circle::CLDisJudge(&c1,&l1));
			Assert::AreEqual(true, Circle::CLDisJudge(&c1,&l2));
			Assert::AreEqual(false, Circle::CLDisJudge(&c1, &l3));
		}
		TEST_METHOD(TestMethod12)
		{
			vector <Shape*> allshape1;
			unordered_set<Point*, Hash_Point, Equal_Point> allpoint1;
			allshape1.emplace_back(ShapeFactory::GetShape("C", 1, 0, 1, 0));
			allshape1.emplace_back(ShapeFactory::GetShape("C", 3, 0, 1, 0));
			GetPoint(allshape1, allpoint1);
			Assert::AreEqual(1, (int)allpoint1.size());
		}
		TEST_METHOD(TestMethod13)
		{
			vector <Shape*> allshape1;
			unordered_set<Point*, Hash_Point, Equal_Point> allpoint1;
			allshape1.emplace_back(ShapeFactory::GetShape("C", 1, 0, 1, 0));
			allshape1.emplace_back(ShapeFactory::GetShape("L", 1, 0, 1, 1));
			GetPoint(allshape1, allpoint1);
			Assert::AreEqual(2, (int)allpoint1.size());
		}
	};
}
