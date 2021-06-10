#include "geometry.h"
#define PI 3.14159265359

Point::Point()
{
    x = 0;
    y = 0;
};

Point::Point(int x_, int y_)
{
    x = x_;
    y = y_;
};

int Point::getX() const
{
    return x;
}

int Point::getY() const
{
    return y;
}

double distance(const Point& a, const Point& b)
{
	double per = sqrt(
		pow(a.getX() - b.getX(), 2) +
		pow(a.getY() - b.getY(), 2));
	return per;
}


PolygonalChain::PolygonalChain(int n_, Point* p_)
{
    p.insert(p.end(), &p_[0], &p_[n_]);
}

int PolygonalChain::getN() const
{
    return p.size();
}

Point PolygonalChain::getPoint(int i) const
{
    return p[i];
}

double PolygonalChain::perimeter() const
{
    double per = 0;
    for (unsigned int i = 1; i < p.size(); i++)
    {
        per += distance(p[i - 1], p[i]);
    }
    return per;
}


ClosedPolygonalChain::ClosedPolygonalChain(int n_, Point* p_) : PolygonalChain(n_, p_) {}

double ClosedPolygonalChain::perimeter() const
{
    double per = PolygonalChain::perimeter();
    per += distance(p[0], p[p.size() - 1]);
    return per;
}


Polygon::Polygon(int n_, Point* p_) : ClosedPolygonalChain(n_, p_) {}

double Polygon::area() const
{
    int s = 0;
    for (unsigned int i = 0; i < p.size() - 1; i++)
    {
        s += p[i].getX()* p[i + 1].getY() - p[i + 1].getX() * p[i].getY();
    }
    s += p[p.size() - 1].getX() * p[0].getY() - p[0].getX() * p[p.size() - 1].getY();
    return abs(s) / 2;
}


Point vectorCreate(const Point& a, const Point& b)
{
    Point c(a.getX() - b.getX(), a.getY() - b.getY());
    return c;
}

bool perpendicularCheck(const Point& a, const Point& b)
{
    int c = (a.getX() * b.getX() + a.getY() * b.getY());
    return (c == 0);
}


Triangle::Triangle(int n_, Point* p_) : Polygon(n_, p_) {}

bool Triangle::hasRightAngle() const
{
    Point a = vectorCreate(p[0], p[1]);
    Point b = vectorCreate(p[1], p[2]);
    Point c = vectorCreate(p[2], p[0]);
    return perpendicularCheck(a, b) || perpendicularCheck(b, c) || perpendicularCheck(a, c);
}


Line::Line(const Point& a, const Point& b)
{
    A = b.getY() - a.getY();
    B = a.getX() - b.getX();
    C = b.getX() * a.getY() - a.getX() * b.getY();
}

int Line::getA() const
{
    return A;
}

int Line::getB() const
{
    return B;
}

int Line::getC() const
{
    return C;
}

void Line::multiplication(int t)
{
    A *= t;
    B *= t;
    C *= t;
}


Trapezoid::Trapezoid(int n_, Point* p_) : Polygon(n_, p_) {}
double Trapezoid::height() const
{
    Line a(p[0], p[3]);
    Line b(p[1], p[2]);
    if (a.getA() != 0)
    {
        int bA = b.getA();
        b.multiplication(a.getA());
        a.multiplication(bA);
    }
    else if (b.getB() != 0)
    {
        int bB = b.getB();
        b.multiplication(a.getB());
        a.multiplication(bB);
    }
    else return 0;
    double h = abs(b.getC() - a.getC()) /
        sqrt(pow(a.getA(), 2) + pow(a.getB(), 2));
    return h;
}


RegularPolygon::RegularPolygon(int n_, Point* p_) : Polygon(n_, p_) {}

double RegularPolygon::perimeter() const
{
    double per = p.size() * distance(p[0], p[1]);
    return per;
}

double RegularPolygon::area() const
{
    double a = distance(p[0], p[1]);
    double s = p.size() * pow(a, 2) / (4 * tan(PI / p.size()));
    return s;
}
