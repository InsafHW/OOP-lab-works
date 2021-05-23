#include <iostream>
#include <sstream>
#include <Windows.h>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

#include "../Task1.ГеометрическиеФигуры/CPoint.h"
#include "../Task1.ГеометрическиеФигуры/IShape.h"
#include "../Task1.ГеометрическиеФигуры/CLineSegment.h"
#include "../Task1.ГеометрическиеФигуры/CTriangle.h"
#include "../Task1.ГеометрическиеФигуры/CRectangle.h"
#include "../Task1.ГеометрическиеФигуры/CCircle.h"
#include "../Task1.ГеометрическиеФигуры/CShapeController.h"

SCENARIO("Тест. LineSegment")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	CLineSegment line({ 1, 1 }, { 1, 2 });
	cout << "--------------------LineSegment--------------------" << endl;
	cout << "Площадь отрезка 0" << endl;
	REQUIRE(line.GetArea() == 0);
	cout << "Периметр равен длине отрезка, т.е. сумме квадратов разности координат" << endl;
	REQUIRE(line.GetPerimeter() == 1);
	cout << "Стандартный цвет обводки черный" << endl;
	REQUIRE(line.GetOutlineColor() == 0xFF0000);
	cout << "Есть возможность изменить начальные координаты" << endl;
	CPoint startPoint = { 4, 0 };
	line.SetStartPoint(startPoint);
	REQUIRE(line.GetStartPoint() == startPoint);
	cout << "Есть возможность изменить конечные координаты" << endl;
	CPoint endPoint = { 6, 0 };
	line.SetEndPoint(endPoint);
	REQUIRE(line.GetEndPoint() == endPoint);
	cout << "Есть возможность изменить цвет обводки" << endl;
	uint32_t newColor = 0xFFFFFFFF;
	line.SetOutlineColor(newColor);
	REQUIRE(line.GetOutlineColor() == newColor);
	cout << "Можно просмотреть информацию об отрезке" << endl;
	string expectedOutput = "Фигура: отрезок;\n"
		"Начальные координаты: (8.000000 ; 0.000000);\n"
		"Конечные координаты: (8.000000 ; 10.000000);\n"
		"Площадь: 0.000000;\n"
		"Периметр: 10.000000;\n"
		"Цвет обводки: 0fffffff\n";
	CLineSegment line2({ 8, 0 }, { 8, 10 }, 0xFFFFFFF);
	REQUIRE(line2.ToString() == expectedOutput);
}

SCENARIO("Тест. Triangle")
{
	cout << "--------------------Triangle--------------------" << endl;
	CTriangle triangle({ 0, 0 }, { 4, 3 }, { 8, 0 });
	cout << "Сторона равна корню суммы квадратов разности координат" << endl;
	REQUIRE(triangle.GetSide12() == 5);
	REQUIRE(triangle.GetSide23() == 5);
	REQUIRE(triangle.GetSide31() == 8);
	cout << "Площадь равна корню из произведения полупереметра на (полупер. - сторона1) на (полупер. - сторона2) на (полупер. - сторона3)" << endl;
	REQUIRE(triangle.GetArea() == 12);
	cout << "Периметр равен сумме длин сторон" << endl;
	REQUIRE(triangle.GetPerimeter() == triangle.GetSide12() + triangle.GetSide23() + triangle.GetSide31());
	cout << "Стандартный цвет обводки черный" << endl;
	REQUIRE(triangle.GetOutlineColor() == 0xFF0000);
	cout << "Стандартный цвет заливки черный" << endl;
	REQUIRE(triangle.GetFillColor() == 0xFF0000);
	cout << "Есть возможность изменить координаты вершин" << endl;
	CPoint vert1 = { 1, 1 };
	CPoint vert2 = { 5, 4 };
	CPoint vert3 = { 9, 1 };
	triangle.SetVertex1(vert1);
	triangle.SetVertex2(vert2);
	triangle.SetVertex3(vert3);
	REQUIRE(triangle.GetVertex1() == vert1);
	REQUIRE(triangle.GetVertex2() == vert2);
	REQUIRE(triangle.GetVertex3() == vert3);
	cout << "Есть возможность изменить цвет обводки" << endl;
	uint32_t newOutlineColor = 0xFFFFFF;
	uint32_t newFillColor = 0xFFFFFF;
	triangle.SetOutlineColor(newOutlineColor);
	triangle.SetFillColor(newFillColor);
	REQUIRE(triangle.GetFillColor() == newFillColor);
	REQUIRE(triangle.GetOutlineColor() == newOutlineColor);
	cout << "Можно посмотреть информацию о треугольнике" << endl;
	string expectedOutput = "Фигура: треугольник;\n"
		"Координаты вершины 1: (1.000000 ; 1.000000);\n"
		"Координаты вершины 2: (5.000000 ; 4.000000);\n"
		"Координаты вершины 3: (9.000000 ; 1.000000);\n"
		"Площадь: 12.000000;\n"
		"Периметр: 18.000000;\n"
		"Цвет обводки: 00ffffff;\n"
		"Цвет заливки: 00ffffff;\n";
	REQUIRE(triangle.ToString() == expectedOutput);
}

SCENARIO("Тест. Rectangle")
{
	cout << "--------------------Rectangle--------------------" << endl;
	CRectangle rectangle({ 0, 10 }, 15, 10);
	cout << "Площадь равна произведению высоты на ширину" << endl;
	REQUIRE(rectangle.GetArea() == rectangle.GetWidth() * rectangle.GetHeight());
	cout << "Периметр равен удвоенной сумме высоты и ширины" << endl;
	REQUIRE(rectangle.GetPerimeter() == rectangle.GetWidth() * 2 + rectangle.GetHeight() * 2);
	cout << "Стандартный цвет обводки черный" << endl;
	REQUIRE(rectangle.GetOutlineColor() == 0xFF0000);
	cout << "Стандартный цвет заливки черный" << endl;
	REQUIRE(rectangle.GetFillColor() == 0xFF0000);
	cout << "Есть возможность изменить коорд. левого верхнего угла" << endl;
	CPoint topLeft = { 10, 10 };
	rectangle.SetLeftTop(topLeft);
	REQUIRE(rectangle.GetLeftTop() == topLeft);
	cout << "Есть возможность изменить высоту" << endl;
	double height = 5;
	double width = 12;
	rectangle.SetHeight(height);
	REQUIRE(rectangle.GetHeight() == height);
	cout << "Есть возможность изменить ширину" << endl;
	rectangle.SetWidth(width);
	REQUIRE(rectangle.GetWidth() == width);
	cout << "Есть возможность изменить цвет обводки" << endl;
	uint32_t newOutlineColor = 0xFFFFFF;
	uint32_t newFillColor = 0xFFFFFF;
	rectangle.SetOutlineColor(newOutlineColor);
	rectangle.SetFillColor(newFillColor);
	REQUIRE(rectangle.GetFillColor() == newFillColor);
	REQUIRE(rectangle.GetOutlineColor() == newOutlineColor);
	cout << "Можно посмотреть информацию о прямоугольнике" << endl;
	string expectedOutput = "Фигура: прямоугольник;\n"
		"Координаты левого верхнего угла: (10.000000 ; 10.000000);\n"
		"Высота: 5.000000;\n"
		"Ширина: 12.000000;\n"
		"Координаты нижнего правого угла: (22.000000 ; 15.000000);\n"
		"Площадь: 60.000000;\n"
		"Периметр: 34.000000;\n"
		"Цвет обводки: 00ffffff;\n"
		"Цвет заливки: 00ffffff;\n";
	REQUIRE(rectangle.ToString() == expectedOutput);
}

SCENARIO("Тест. Окружность")
{
	cout << "--------------------Circle--------------------" << endl;
	CCircle circle({ 10, 10 }, 5);
	cout << "Площадь равна PI * радиус в квадрате" << endl;
	REQUIRE(circle.GetArea() == 3.14 * 25);
	cout << "Периметер \ Длина окружности равна 2 PI * радиус" << endl;
	REQUIRE(circle.GetPerimeter() == 2 * 3.14 * 5);
	cout << "Стандартный цвет обводки черный" << endl;
	REQUIRE(circle.GetOutlineColor() == 0xFF0000);
	cout << "Стандартный цвет заливки черный" << endl;
	REQUIRE(circle.GetFillColor() == 0xFF0000);
	cout << "Есть возможность изменить радиус" << endl;
	double radius = 10;
	circle.SetRadius(radius);
	REQUIRE(circle.GetRadius() == radius);
	cout << "Есть возможность изменить центр" << endl;
	CPoint center = { 0, 0 };
	circle.SetCenter(center);
	REQUIRE(circle.GetCenter() == center);
	cout << "Есть возможность изменить цвет обводки" << endl;
	uint32_t newOutlineColor = 0xFFFFFF;
	uint32_t newFillColor = 0xFFFFFF;
	circle.SetOutlineColor(newOutlineColor);
	circle.SetFillColor(newFillColor);
	REQUIRE(circle.GetFillColor() == newFillColor);
	REQUIRE(circle.GetOutlineColor() == newOutlineColor);
	cout << "Можно посмотреть информацию об окружности" << endl;
	string expectedOutput = "Фигура: окружность;\n"
		"Координаты центра: (0.000000 ; 0.000000);\n"
		"Радиус: 10.000000;\n"
		"Площадь: 314.000000;\n"
		"Длина окружности: 62.800000;\n"
		"Цвет обводки: 00ffffff;\n"
		"Цвет заливки: 00ffffff;\n";
	REQUIRE(circle.ToString() == expectedOutput);
}

SCENARIO("CShapeController. LineSegment")
{
	cout << "--------------------ShapeController.LineSegment--------------------" << endl;
	ostringstream output;
	CShapeController controller(output);
	cout << "Если у отрезка ввести невалидные точки (буквы, символы), то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("line f 0 10 23 ff0000") == false);
	REQUIRE(controller.ReadShape("line 3 0 f 23 ff0000") == false);
	REQUIRE(controller.ReadShape("line 3 f 10 23 ff0000") == false);
	REQUIRE(controller.ReadShape("line 3 4 10 uj ff0000") == false);
	cout << "Если у отрезка ввести невалидный цвет, то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("line 2 0 10 23 ffh000") == false);
	cout << "Если у отрезка валидные точки, но не указать цвет, то установиться стандартный - ff0000" << endl;
	REQUIRE(controller.ReadShape("line 0 0 10 23") == true);
	(*controller.GetLastShape()).GetOutlineColor();
	REQUIRE((*controller.GetLastShape()).GetOutlineColor() == 0xFF0000);
	cout << "Если у отрезка валидные точки, и передан валидный цвет, то объект создатся" << endl;
	REQUIRE(controller.ReadShape("line 0 0 10 15 ff113a") == true);
	cout << "Если у отрезка валидные точки, и не передан цвет, то объект создатся" << endl;
	REQUIRE(controller.ReadShape("line 0 0 10 15") == true);

}

SCENARIO("CShapeController. Triangle")
{
	cout << "--------------------ShapeController.Triangle--------------------" << endl;
	ostringstream output;
	CShapeController controller(output);
	cout << "Если у треугольника ввести невалидные точки (буквы, символы), то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("triangle a 0 12 6 7 8 ff0000") == false);
	REQUIRE(controller.ReadShape("triangle 0 a 12 6 7 8 ff0000") == false);
	REQUIRE(controller.ReadShape("triangle 0 0 a 6 7 8 ff0000") == false);
	REQUIRE(controller.ReadShape("triangle 0 0 12 a 7 8 ff0000") == false);
	REQUIRE(controller.ReadShape("triangle 0 0 12 6 a 8 ff0000") == false);
	REQUIRE(controller.ReadShape("triangle 0 0 12 6 7 a ff0000") == false);
	cout << "Если у треугольника ввести невалидный цвет обводки, то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("triangle 0 0 12 6 7 8 ff000g") == false);
	cout << "Если у треугольника ввести невалидный цвет заливки, то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("triangle 0 0 12 6 7 8 ff0000 ffg000") == false);
	cout << "Если у треугольника валидные точки, и указать валидные цвета обводки и заливки, то объект создатся" << endl;
	REQUIRE(controller.ReadShape("triangle 0 0 12 6 7 8 ff0000 ff4000") == true);
	cout << "Если у треугольника валидные точки, и указать валидные цвет обводки, но не указать цвет заливки, то объект создатся" << endl;
	REQUIRE(controller.ReadShape("triangle 0 0 12 6 7 8 ff0000") == true);
	cout << "Если у треугольника валидные точки, но не указать цвет обводки и заливки, то объект создатся" << endl;
	controller.ReadShape("triangle 0 0 12 6 7 8");
	REQUIRE(controller.ReadShape("triangle 0 0 12 6 7 8") == true);
}

SCENARIO("CShapeController. Rectangle")
{
	cout << "--------------------ShapeController.Rectangle--------------------" << endl;
	ostringstream output;
	CShapeController controller(output);
	cout << "Если у прямоугольника ввести невалидные точки (буквы, символы) или невалидную ширину / высоту , то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("rectangle a 3 30 40") == false);
	REQUIRE(controller.ReadShape("rectangle 0 a 30 40") == false);
	REQUIRE(controller.ReadShape("rectangle 0 3 f 40") == false);
	REQUIRE(controller.ReadShape("rectangle 0 3 30 v") == false);
	cout << "Если у прямоугольника ввести отрицательную ширину, то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 -30 40") == false);
	cout << "Если у прямоугольника ввести отрицательную высоту, то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 30 -40") == false);
	cout << "Если у прямоугольника ввести невалидный цвет обводки, то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 30 40 ff3") == false);
	cout << "Если у прямоугольника ввести невалидный цвет заливки, то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 30 40 ff0000 ff3") == false);
	cout << "Если у прямоугольника валидные точки, ширина и высота, и указать валидные цвета обводки и заливки, то объект создатся" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 30 40 ff0000 ff0000") == true);
	cout << "Если у прямоугольника валидные точки, ширина и высота, и указать валидный цвет обводки, но не задать цвет заливки, то объект создатся" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 30 40 ff0000") == true);
	cout << "Если у прямоугольника валидные точки, ширина и высота, но не указать цвет обводки и цвет заливки, то объект создатся" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 30 40") == true);
}

SCENARIO("CShapeController. Circle")
{
	cout << "--------------------ShapeController.Circle--------------------" << endl;
	ostringstream output;
	CShapeController controller(output);
	cout << "Если у окружности ввести невалидные точки (буквы, символы) или невалидный радиус, то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("circle a 0 3") == false);
	REQUIRE(controller.ReadShape("circle 0 a 3") == false);
	REQUIRE(controller.ReadShape("circle 0 0 a") == false);
	cout << "Если у окружности ввести отрицательный радиус, то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("circle 0 0 -5") == false);
	cout << "Если у окружности ввести невалидный цвет обводки, то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("circle 0 0 5 ff2") == false);
	cout << "Если у окружности ввести невалидный цвет заливки, то выдаст ошибку" << endl;
	REQUIRE(controller.ReadShape("circle 0 0 5 ff0000 ff2") == false);
	cout << "Если у окружности валидные точки, радиус, и указать валидные цвета обводки и заливки, то объект создатся" << endl;
	REQUIRE(controller.ReadShape("circle 0 0 5 ff0000 ff0000") == true);
	cout << "Если у окружности валидные точки, радиус, и указать валидный цвет обводки, но не задать цвет заливки, то объект создатся" << endl;
	REQUIRE(controller.ReadShape("circle 0 0 5 ff0000") == true);
	cout << "Если у окружности валидные точки, радиус, но не указать цвет обводки и цвет заливки, то объект создатся" << endl;
	REQUIRE(controller.ReadShape("circle 0 0 5") == true);
}

SCENARIO("CShapeController. GetMinPerimeterInfo")
{
	cout << "--------------------ShapeController.GetMinPerimeterInfo--------------------" << endl;
	ostringstream output;
	CShapeController controller(output);
	cout << "Если не введены фигуры и вызвать функцию, то напечатет нет фигур" << endl;
	controller.GetMinPerimeterInfo();
	REQUIRE(output.str() == "Нет фигур\n");
	output.str("");
	cout << "Если введена только одна фигура, то выведет информацию о ней" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 10 15") == true);
	controller.GetMinPerimeterInfo();
	string expectedOutput = "Фигура с минимальным периметром: \n"
		"Фигура: прямоугольник;\n"
		"Координаты левого верхнего угла: (0.000000 ; 0.000000);\n"
		"Высота: 15.000000;\n"
		"Ширина: 10.000000;\n"
		"Координаты нижнего правого угла: (10.000000 ; 15.000000);\n"
		"Площадь: 150.000000;\n"
		"Периметр: 50.000000;\n"
		"Цвет обводки: 00ff0000;\n"
		"Цвет заливки: 00ff0000;\n";
	REQUIRE(output.str() == expectedOutput);
	cout << "Если введено несколько фигур, то выведет информацию у которой меньший периметр" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 19 15") == true);
	output.str("");
	controller.GetMinPerimeterInfo();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("CShapeController. GetMaxSquareInfo")
{
	cout << "--------------------ShapeController.GetMaxSquareInfo--------------------" << endl;
	ostringstream output;
	CShapeController controller(output);
	controller.GetMaxSquareInfo();
	REQUIRE(output.str() == "Нет фигур\n");
	output.str("");
	cout << "Если введена только одна фигура, то выведет информацию о ней" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 10 15") == true);
	controller.GetMaxSquareInfo();
	string expectedOutput = "Фигура с максимальной площадью: \n"
		"Фигура: прямоугольник;\n"
		"Координаты левого верхнего угла: (0.000000 ; 0.000000);\n"
		"Высота: 15.000000;\n"
		"Ширина: 10.000000;\n"
		"Координаты нижнего правого угла: (10.000000 ; 15.000000);\n"
		"Площадь: 150.000000;\n"
		"Периметр: 50.000000;\n"
		"Цвет обводки: 00ff0000;\n"
		"Цвет заливки: 00ff0000;\n";
	REQUIRE(output.str() == expectedOutput);
	cout << "Если введено несколько фигур, то выведет информацию у которой большая площадь" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 19 15") == true);
	output.str("");
	expectedOutput = "Фигура с максимальной площадью: \n"
		"Фигура: прямоугольник;\n"
		"Координаты левого верхнего угла: (0.000000 ; 0.000000);\n"
		"Высота: 15.000000;\n"
		"Ширина: 19.000000;\n"
		"Координаты нижнего правого угла: (19.000000 ; 15.000000);\n"
		"Площадь: 285.000000;\n"
		"Периметр: 68.000000;\n"
		"Цвет обводки: 00ff0000;\n"
		"Цвет заливки: 00ff0000;\n";
	controller.GetMaxSquareInfo();
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("CShapeController. WriteInfos")
{
	cout << "--------------------ShapeController.WriteInfos--------------------" << endl;
	ostringstream output;
	CShapeController controller(output);
	cout << "Если не введены фигуры и вызвать функцию, то напечает нет фигур" << endl;
	controller.WriteInfos();
	REQUIRE(output.str() == "Нет фигур\n");
	output.str("");
	cout << "Если введена только одна фигура, то выведет информацию о ней" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 10 15") == true);
	controller.WriteInfos();
	string expectedOutput = "Фигура: прямоугольник;\n"
		"Координаты левого верхнего угла: (0.000000 ; 0.000000);\n"
		"Высота: 15.000000;\n"
		"Ширина: 10.000000;\n"
		"Координаты нижнего правого угла: (10.000000 ; 15.000000);\n"
		"Площадь: 150.000000;\n"
		"Периметр: 50.000000;\n"
		"Цвет обводки: 00ff0000;\n"
		"Цвет заливки: 00ff0000;\n\n";
	REQUIRE(output.str() == expectedOutput);
	cout << "Если введено несколько фигур, то выведет информацию обо всех в порядке их чтения" << endl;
	REQUIRE(controller.ReadShape("rectangle 0 0 19 15") == true);
	output.str("");
	controller.WriteInfos();
	expectedOutput = "Фигура: прямоугольник;\n"
		"Координаты левого верхнего угла: (0.000000 ; 0.000000);\n"
		"Высота: 15.000000;\n"
		"Ширина: 10.000000;\n"
		"Координаты нижнего правого угла: (10.000000 ; 15.000000);\n"
		"Площадь: 150.000000;\n"
		"Периметр: 50.000000;\n"
		"Цвет обводки: 00ff0000;\n"
		"Цвет заливки: 00ff0000;\n\n"
		"Фигура: прямоугольник;\n"
		"Координаты левого верхнего угла: (0.000000 ; 0.000000);\n"
		"Высота: 15.000000;\n"
		"Ширина: 19.000000;\n"
		"Координаты нижнего правого угла: (19.000000 ; 15.000000);\n"
		"Площадь: 285.000000;\n"
		"Периметр: 68.000000;\n"
		"Цвет обводки: 00ff0000;\n"
		"Цвет заливки: 00ff0000;\n\n";
	REQUIRE(output.str() == expectedOutput);
}