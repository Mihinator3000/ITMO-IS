#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include <vector>
#include <math.h>

class Point
{
private:
	int x;
	int y;
public:
	Point();
	Point(int, int);
	int getX() const;
	int getY() const;
};


double distance(const Point&, const Point&);


class PolygonalChain
{
protected:
	std::vector<Point> p;
public:
	PolygonalChain(int, Point*);
	int getN() const;
	Point getPoint(int) const;
	virtual double perimeter() const;
	virtual ~PolygonalChain() {}
};


class ClosedPolygonalChain: public PolygonalChain
{
public:
	ClosedPolygonalChain(int, Point*);
	double perimeter() const override;
};


class Polygon : public ClosedPolygonalChain
{
public:
	Polygon(int, Point*);
	virtual double area() const;
};


Point vectorCreate(const Point&, const Point&);

bool perpendicularCheck(const Point&, const Point&);


class Triangle : public Polygon
{
public:
	Triangle(int, Point*);
	bool hasRightAngle() const;
};


class Line
{
private:
	int A;
	int B;
	int C;
public:
	Line(const Point&, const Point&);
	int getA() const;
	int getB() const;
	int getC() const;
	void multiplication(int);
};


class Trapezoid : public Polygon
{
public:
	Trapezoid(int, Point*);
	double height() const;
};


class RegularPolygon : public Polygon
{
public:
	RegularPolygon(int, Point*);
	double perimeter() const override;
	double area() const override;
};

#endif // GEOMETRY_H_INCLUDED
