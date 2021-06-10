#include "polynomial.h"
#include <math.h>

Polynomial::Polynomial()
{
	n = 0;
	k = 0;
	p = new int[1]{0};
}

Polynomial::Polynomial(int n_, int k_, int* p_)
{
	n = n_;
	k = k_;
	p = new int[k - n + 1];
	for (int i = 0; i <= k - n; i++)
    {
        p[i] = p_[i];
    }
}

Polynomial::Polynomial(const Polynomial& s)
{
    n = s.n;
	k = s.k;
	p = new int[k - n + 1];
	for (int i = 0; i <= k - n; i++)
	{
	    p[i] = s.p[i];
	}
}

Polynomial::~Polynomial()
{
    delete [] p;
}

double Polynomial::get(int a) const
{
    double answer = 0;
    if (n <= 0 && 0 <= k)
    {
        answer += p[-n];
    }
    double powermult = 1;
    double maxpower = std::max(abs(n), abs(k));
    for (int i = 1; i <= maxpower; i++)
    {
        powermult *= a;
        if (n <= i && i <= k)
        {
            answer += p[i - n] * powermult;
        }
        if (n <= -i && -i <= k)
        {
            answer += p[-i - n] / powermult;
        }
    }
    return answer;
}

Polynomial& Polynomial::operator=(const Polynomial& s)
{
    if (this == &s)
    {
        return *this;
    }
    n = s.n;
	k = s.k;
	delete[] p;
	p = new int[k - n + 1];
	for (int i = 0; i <= k - n; i++)
	{
	    p[i] = s.p[i];
	}
	return *this;

}

bool Polynomial::operator==(const Polynomial& s) const
{
	int minn = std::min(n, s.n);
	int maxk = std::max(k, s.k);
	for (int i = minn; i <= maxk; i++)
    {
        if (i < n || i > k)
        {
            if (s.p[i - s.n] != 0)
            {
                return false;
            }
            continue;
        }
        if (i < s.n || i > s.k)
        {
            if (p[i - n] != 0)
            {
                return false;
            }
            continue;
        }
        if (p[i - n] != s.p[i - s.n])
        {
            return false;
        }
    }
    return true;
}

bool Polynomial::operator!=(const Polynomial& s) const
{
	return !(*this == s);
}

//todo + from += (done)


void Polynomial::SummDiff(const Polynomial& s, int plusOrMinus)
{
    if (n <= s.n && s.k <= k)
    {
        for (int i = n; i <= k; i++)
        {
            if (i >= s.n && i <= s.k)
                p[i - n] += s.p[i - s.n] * plusOrMinus;
        }
        return;
    }
	int n_ = std::min(n, s.n);
	int k_ = std::max(k, s.k);
	int* p_ = new int[k_ - n_ + 1];
	for (int i = n_; i <= k_; i++)
	{
		if (i < n || i > k)
		{
		    p_[i - n_] = s.p[i - s.n] * plusOrMinus;
			continue;
		}
		if (i < s.n || i > s.k)
		{
            p_[i - n_] = p[i - n];
			continue;
		}
        p_[i - n_] = p[i - n] + s.p[i - s.n] * plusOrMinus;
	}
	n = n_;
	k = k_;
	delete [] p;
    p = p_;
}

Polynomial& Polynomial::operator+=(const Polynomial& s)
{
    SummDiff(s, 1);
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& s)
{
	SummDiff(s, -1);
	return *this;
}

Polynomial Polynomial::operator+(const Polynomial& s) const
{
    Polynomial c = s;
	return c += *this;
}


Polynomial Polynomial::operator-(const Polynomial& s) const
{
	Polynomial c = s;
	return c -= *this;
}

Polynomial Polynomial::operator-() const
{
    Polynomial c = *this;
	for (int i = 0; i <= k - n; i++)
	{
	    c.p[i] = -c.p[i];
	}
	return c;
}

Polynomial& Polynomial::operator*=(const Polynomial& s)
{
	int n_ = n + s.n;
	int k_ = k + s.k;
	int* p_ = new int[k_ - n_ + 1];
	int minn = std::min(n, s.n);
	int maxk = std::max(k, s.k);
	for (int i = n_; i <= k_; i++)
	{
		int num = 0;
		for (int j = minn; j <= maxk; j++)
		{
			if ((j - n >= 0) &&
				(j <= k) &&
				(i - j - s.n >= 0) &&
				(i - j <= s.k))
			{
				num += p[j - n] * s.p[i - j - s.n];
			}
		}
		p_[i - n_] = num;
	}
	n = n_;
	k = k_;
	delete[] p;
	p = p_;
	return *this;
}

Polynomial& Polynomial::operator/=(const int s)
{
	for (int i = 0; i <= k - n; i++)
	{
	    p[i] /= s;
	}
	return *this;
}

Polynomial Polynomial::operator*(const Polynomial& s) const
{
	Polynomial c = *this;
	c *= s;
	return c;
}

Polynomial Polynomial::operator/(const int s) const
{
	Polynomial c = *this;
	c /= s;
	return c;
}

Polynomial operator*(const Polynomial& s, int a)
{
    Polynomial c = s;
	for (int i = 0; i <= s.k - s.n; i++)
	{
	    c.p[i] = s.p[i] * a;
	}
	return c;
}

Polynomial operator*(int a, const Polynomial& s)
{
    return s * a;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& s)
{
    bool check = false;
	for (int i = s.k; i >= s.n; i--)
	{
		int c = s[i];
		if (c != 0)
		{
			if (c > 0)
			{
				if (check)
					out << "+";
			}
			else
			{
				out << "-";
			}
			c = abs(c);
			if (c != 1)
			{
				out << c;
			}
			else if (i == 0)
			{
				out << c;
			}
			if (i != 0)
			{
				out << "x";
				if (i != 1)
                    out << "^" << i;
			}
		    check = true;
		}
	}
	if (!check)
    {
        out << "0";
    }
	return out;
}

std::istream& operator>>(std::istream& in, Polynomial& s)
{
	in >> s.n;
	in >> s.k;
	s.p = new int[s.k - s.n + 1];
	for (int i = 0; i <= s.k - s.n; i++)
	{
		in >> s.p[i];
	}
	return in;
}

int& Polynomial::operator[](const int index)
{
    if (n <= index && index <= k)
    {
        return p[index - n];
    }
    int n_ = n;
    int k_ = k;
    if (index < n)
    {
        n_ = index;
    }
    if (index > k)
    {
        k_ = index;
    }
    int* p_ = new int[k_ - n_ + 1];
    for (int i = n_; i <= k_; i++)
    {
        if (i >= n && i <= k)
        {
            p_[i - n_] = p[i - n];
        }
        else
        {
            p_[i - n_] = 0;
        }
    }
    n = n_;
    k = k_;
    delete [] p;
    p = p_;
    return p[index - n];
}

int Polynomial::operator[](const int index) const
{
    if (index >= n && index <= k)
    {
        return p[index - n];
    }
    return 0;
}
