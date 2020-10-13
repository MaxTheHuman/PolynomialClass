#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

// using namespace std;

template <typename T>
class Polynomial{
public:
    Polynomial(const std::vector<T>& new_vector);
    Polynomial(const T& constant = T(0));

    template <class InputIt1, class InputIt2>
    Polynomial(const InputIt1& in_it, const InputIt2& out_it);
    
    typename std::vector<std::pair<size_t, T> >::const_iterator begin() const;
    typename std::vector<std::pair<size_t, T> >::const_iterator end() const;

    int Degree() const;

    T operator[] (size_t deg) const;

    const Polynomial<T>& operator+= (const Polynomial<T>& poly_right);
    const Polynomial<T>& operator+= (const T& scalar_right);
    Polynomial<T> operator+ (const Polynomial<T>& poly_right) const;
    Polynomial<T> operator+ (const T& scalar_right) const;

    Polynomial<T>& operator-= (const Polynomial<T>& poly_right);
    Polynomial<T>& operator-= (const T& scalar_right);
    const Polynomial<T> operator- (const Polynomial<T>& poly_right) const;
    const Polynomial<T> operator- (const T& scalar_right) const;

    bool operator== (const Polynomial<T>& other) const;
    bool operator== (const T& scalar) const;
    bool operator != (const Polynomial<T>& other) const;
    bool operator!= (const T& scalar) const;

    T operator() (const T& coordinate) const;

    Polynomial<T>& operator*= (const Polynomial<T>& poly_right);
    Polynomial<T>& operator*= (const T& scalar_right);
    Polynomial<T> operator* (const Polynomial<T>& poly_right) const;
    Polynomial<T> operator* (const T& scalar_right) const;

    Polynomial<T> operator& (const Polynomial<T>& poly_right) const;

    Polynomial<T> operator/ (const Polynomial<T>& poly_right) const;

    Polynomial<T> operator% (const Polynomial<T>& poly_right) const;

    Polynomial<T> operator, (const Polynomial<T>& poly_right) const;  // GCD

private:
    std::vector<std::pair<size_t, T> > coefficients;
};

template <typename T>
const Polynomial<T> operator+ (const T& scalar_left,
                               const Polynomial<T>& poly_right);

template <typename T>
const Polynomial<T> operator- (const T& scalar_left,
                               const Polynomial<T>& poly_right) ;

template <typename T>
Polynomial<T> operator* (const T& scalar_left,
                         const Polynomial<T>& poly_right);

template <typename T>
bool operator== (T scalar, Polynomial<T>& other);

template <typename T>
bool operator!= (T scalar, Polynomial<T>& other);

template <typename T>
ostream& operator<<(ostream& out, const Polynomial<T>& poly);
