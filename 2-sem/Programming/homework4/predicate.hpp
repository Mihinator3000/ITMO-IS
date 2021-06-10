#ifndef PREDICATE_HPP
#define PREDICATE_HPP

template <class I, class P>
bool allOf(I b, I e, P p)
{
    for (I i = b; i != e; i++)
    {
        if (!p(*i))
            return false;
    }
    return true;
}

template <class I, class P>
bool anyOf(I b, I e, P p)
{
    for (I i = b; i != e; i++)
    {
        if (p(*i))
            return true;
    }
    return false;
}

template <class I, class P>
bool noneOf(I b, I e, P p)
{
    for (I i = b; i != e; i++)
    {
        if (p(*i))
            return false;
    }
    return true;
}

template <class I, class P>
bool oneOf(I b, I e, P p)
{
    bool check = false;
    for (I i = b; i != e; i++)
    {
        if (p(*i))
        {
            if (check)
                return false;
            check = true;
        }
    }
    return check;
}

template <class I, class P>
bool isSorted(I b, I e, P p)
{
    e--;
    for (I i = b; i != e;)
    {
        if (p(*i, *(i++)))
            return false;

    }
    return true;
}

template <class I>
bool isSorted(I b, I e)
{
    e--;
    for (I i = b; i != e;)
    {
        if(*i > *(i++))
            return false;
    }
    return true;
}

template <class I, class P>
bool isPartitioned(I b, I e, P p)
{
    bool check = p(*b);
    bool changed = false;
    for (I i = b; i != e; i++)
    {
        if (p(*i) != check)
        {
            if (changed)
                return false;
            changed = true;
            check = !check;
        }
    }
    return changed;
}

template <class I, class T>
I findNot(I b, I e, const T& t)
{
    for (I i = b; i != e; i++)
    {
        if (*i != t)
            return i;
    }
    return e;
}

template <class I, class T>
I findBackward(I b, I e, const T& t)
{
    I j = e;
    for (I i = b; i != e; i++)
    {
        if (*i == t)
            j = i;
    }
    return j;
}

template <class I, class P>
bool isPalindrome(I b, I e, P p)
{
    I i = b;
    I j = e;
    j--;
    while (true)
    {
        if (!p(*i, *j))
            return false;
        i++;
        if (i != j)
            j--;
        if (i == j)
            return true;
    }

}

#endif // PREDICATE_HPP
