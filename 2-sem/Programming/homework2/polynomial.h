#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H


#include <iostream>
#include <vector>

class Polynomial
{
private:
	int n, k;
	int* p;
	
    void SummDiff(const Polynomial&, int);
public:
	Polynomial();
	Polynomial(int, int, int*);
	Polynomial(const Polynomial&);
    ~Polynomial();

    double get(int) const;
    Polynomial& operator=(const Polynomial&);

	bool operator==(const Polynomial&) const;
	bool operator!=(const Polynomial&) const;

    Polynomial& operator+=(const Polynomial&);
	Polynomial& operator-=(const Polynomial&);
	Polynomial operator+(const Polynomial&) const;
	Polynomial operator-(const Polynomial&) const;
    Polynomial operator-() const;

    Polynomial& operator*=(const Polynomial&);
	Polynomial& operator/=(const int);
	Polynomial operator*(const Polynomial&) const;
    Polynomial operator/(const int) const;
	friend Polynomial operator*(const Polynomial&, int);
	friend Polynomial operator*(int, const Polynomial&);
	friend std::ostream& operator<<(std::ostream&, const Polynomial&);
	friend std::istream& operator>>(std::istream&, Polynomial&);

	int& operator[](const int);
	int operator[](const int) const;

};

#endif // POLYNOMIAL_H
