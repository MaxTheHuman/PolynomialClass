#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


template <typename T>
class Polynomial{
public:
    vector<pair<size_t, T> > coefficients;

public:
    explicit Polynomial(const vector<T>& new_vector): coefficients() {
        size_t deg = 0;
        for (const T& new_coefficient : new_vector) {
            if (new_coefficient != T(0)) {
                coefficients.push_back(make_pair(deg, new_coefficient));
            }
            deg++;
        }
    }

    explicit Polynomial(const T& constant = T(0)) : coefficients() {
        if (constant != T(0)) {
            coefficients.push_back(make_pair(static_cast<size_t>(0), constant));
        }
    }

    template <class InputIt1, class InputIt2>
    explicit Polynomial(const InputIt1& in_it, const InputIt2& out_it): coefficients() {
        InputIt1 in_copy = in_it;
        size_t deg = 0;
        while (in_copy != out_it) {
            if (*in_copy != T(0)) {
                coefficients.push_back(make_pair(deg, *in_copy));
            }
            in_copy++;
            deg++;
        }
    }

    typename vector<pair<size_t, T> >::const_iterator begin() const {
        return coefficients.begin();
    }

    typename vector<pair<size_t, T> >::const_iterator end() const {
        return coefficients.end();
    }

    int Degree() const {
        if (coefficients.size() == 0) {
            return - 1;
        } else {
            return static_cast<int>(coefficients[coefficients.size() - 1].first);
        }
    }

    T operator[] (size_t deg) const {
        if (static_cast<int>(deg) > Degree()) {
            return T(0);
        }
        for (auto current_pair : coefficients) {
            if (current_pair.first == deg) {
                return current_pair.second;
            }
        }
        return T(0);
    }

    const Polynomial<T>& operator+= (const Polynomial<T>& poly_right) {
        int right_deg = poly_right.Degree();
        int left_deg = Degree();
        vector<pair<size_t, T> > new_vector;
        int new_size = max(right_deg, left_deg);
        for (int i = 0; i <= new_size; i++) {
            T current_sum = (*this)[i] + poly_right[i];
            if (current_sum != T(0)) {
                new_vector.push_back(make_pair(
                                     static_cast<size_t>(i), current_sum));
            }
        }
        coefficients = new_vector;
        return *this;
    }

    const Polynomial<T>& operator+= (const T& scalar_right) {
        Polynomial<T> helper(scalar_right);
        *this += helper;
        return *this;
    }

    Polynomial<T> operator+ (const Polynomial<T>& poly_right) const {
        Polynomial<T> new_poly;
        new_poly = *this;
        new_poly += poly_right;
        return new_poly;
    }

    Polynomial<T> operator+ (const T& scalar_right) const {
        Polynomial<T> new_poly;
        new_poly = *this;
        new_poly += scalar_right;
        return new_poly;
    }

    Polynomial<T>& operator-= (const Polynomial<T>& poly_right) {
        int right_deg = poly_right.Degree();
        int left_deg = Degree();
        vector<pair<size_t, T> > new_vector;
        int new_size = max(right_deg, left_deg);
        for (int i = 0; i <= new_size; i++) {
            T current_diff = (*this)[i] - poly_right[i];
            if (current_diff != T(0)) {
                new_vector.push_back(make_pair(
                                     static_cast<size_t>(i), current_diff));
            }
        }
        coefficients = new_vector;
        return *this;
    }

    Polynomial<T>& operator-= (const T& scalar_right) {
        Polynomial<T> helper(scalar_right);
        *this -= helper;
        return *this;
    }

    const Polynomial<T> operator- (const Polynomial<T>& poly_right) const {
        Polynomial<T> new_poly;
        new_poly = *this;
        new_poly -= poly_right;
        return new_poly;
    }

    const Polynomial<T> operator- (const T& scalar_right) const {
        Polynomial<T> new_poly;
        new_poly = *this;
        new_poly -= scalar_right;
        return new_poly;
    }

    bool operator== (const Polynomial<T>& other) const {
        return coefficients == other.coefficients;
    }
    bool operator== (T scalar) const {
        return ((coefficients.size() == 1 &&
                coefficients[0].second == scalar) ||
                (coefficients.size() == 0 && scalar == T(0)));
    }
    bool operator!= (const Polynomial<T>& other) const {
        return coefficients != other.coefficients;
    }
    bool operator!= (T scalar) const {
        return (!(*this == scalar));
    }

    T operator() (const T& coordinate) const {
        T value = T(0);
        T x = coordinate;
        int i = 0;
        if (i <= Degree()) {
            value += (*this)[i];
            i++;
        }
        for (; i <= Degree(); i++) {
            value += (*this)[i] * x;
            x = x * coordinate;
        }
        return value;
    }

    Polynomial<T>& operator*= (const Polynomial<T>& poly_right) {
        if (coefficients.size() == 0){
            return *this;
        } else if (poly_right.coefficients.size() == 0) {
            coefficients = poly_right.coefficients;
            return *this;
        }
        size_t right_degree = poly_right.Degree();
        size_t left_degree = Degree();
        size_t new_degree = left_degree + right_degree;
        vector<T> new_vector(new_degree + 1, T(0));
        for (auto left_pair : coefficients) {
            for (auto right_pair : poly_right.coefficients) {
                new_vector[left_pair.first + right_pair.first] +=
                        left_pair.second * right_pair.second;
            }
        }
        Polynomial<T> helper(new_vector);
        coefficients = helper.coefficients;
        return *this;
    }

    Polynomial<T>& operator*= (const T& scalar_right) {
        if (coefficients.size() == 0){
            return *this;
        }
        if (scalar_right == T(0)) {
            coefficients = {};
            return *this;
        }
        size_t left_size = coefficients.size();
        vector<T> new_vector(left_size, T());
        for (size_t i = 0; i < left_size; i++) {
            coefficients[i].second *= scalar_right;
        }
        return *this;
    }

    Polynomial<T> operator* (const Polynomial<T>& poly_right) const {
        Polynomial<T> new_poly;
        new_poly = *this;
        new_poly *= poly_right;
        return new_poly;
    }

    Polynomial<T> operator* (const T& scalar_right) const {
        Polynomial<T> new_poly;
        new_poly = *this;
        new_poly *= scalar_right;
        return new_poly;
    }

    Polynomial<T> operator& (const Polynomial<T> poly_right) const {
        if (coefficients.size() > 0) {
            size_t left_degree = Degree();
            Polynomial<T> helper_poly;
            helper_poly = poly_right;
            Polynomial<T> new_poly;
            size_t i = 0;
            if (i <= left_degree) {
                new_poly += (*this)[i];
                i++;
            }
            for (; i <= left_degree; i++) {
                new_poly += (helper_poly * (*this)[i]);
                helper_poly *= poly_right;
            }
            return new_poly;
        } else {
            Polynomial<T> new_poly(T(0));
            return new_poly;
        }
    }

    Polynomial<T> operator/ (const Polynomial<T>& poly_right) const {
        if (coefficients.size() == 0) {
            return *this;
        }
        Polynomial<T> rest;
        rest = *this;
        vector<T> result_vector((Degree() + 1), T(0));
        T new_coefficient = T(0);
        int new_degree;
        while (rest.Degree() >= poly_right.Degree()) {
            new_coefficient = rest[rest.Degree()] /
                poly_right[poly_right.Degree()];
            new_degree = rest.Degree() - poly_right.Degree();
            vector<T> new_vector(new_degree + 1, T(0));
            new_vector[new_degree] = new_coefficient;
            result_vector[new_degree] = new_coefficient;
            Polynomial<T> new_monome(new_vector);
            rest -= (new_monome * poly_right);
        }
        Polynomial<T> full_part(result_vector);
        return full_part;
    }

    Polynomial<T> operator% (const Polynomial<T>& poly_right) const {
        if (coefficients.size() == 0) {
            return *this;
        }
        Polynomial<T> rest;
        rest = *this;
        T new_coefficient = T(0);
        int new_degree;
        while (rest.Degree() >= poly_right.Degree()) {
            new_coefficient = rest[rest.Degree()] /
                poly_right[poly_right.Degree()];
            new_degree = rest.Degree() - poly_right.Degree();
            vector<T> new_vector(new_degree + 1, T(0));
            new_vector[new_degree] = new_coefficient;
            Polynomial<T> new_monome(new_vector);
            rest -= (new_monome * poly_right);
        }
        return rest;
    }

    Polynomial<T> operator, (const Polynomial<T>& poly_right) const {
        Polynomial<T> smaller_poly(T(0));
        Polynomial<T> bigger_poly(T(0));
        Polynomial<T> helper(T(0));
        if (poly_right.Degree() > Degree()) {
            bigger_poly = poly_right;
            smaller_poly = *this;
        } else {
            bigger_poly = *this;
            smaller_poly = poly_right;
        }
        while (smaller_poly != T(0)) {
            helper = bigger_poly % smaller_poly;
            bigger_poly = smaller_poly;
            smaller_poly = helper;
        }
        if (bigger_poly != T(0)) {
            Polynomial<T> divider(bigger_poly[bigger_poly.Degree()]);
            bigger_poly = bigger_poly / divider;
        }
        return bigger_poly;
    }
};

template <typename T>
const Polynomial<T> operator+ (const T& scalar_left,
                               const Polynomial<T>& poly_right) {
    Polynomial<T> new_poly;
    new_poly = poly_right;
    new_poly += scalar_left;
    return new_poly;
}

template <typename T>
const Polynomial<T> operator- (const T& scalar_left,
                               const Polynomial<T>& poly_right) {
    Polynomial<T> new_poly;
    new_poly += scalar_left;
    new_poly -= poly_right;
    return new_poly;
}

template <typename T>
Polynomial<T> operator* (const T& scalar_left,
                         const Polynomial<T>& poly_right) {
    Polynomial<T> new_poly;
    new_poly = poly_right;
    new_poly *= scalar_left;
    return new_poly;
}

template <typename T>
bool operator== (T scalar, Polynomial<T>& other) {
    return other == scalar;
}

template <typename T>
bool operator!= (T scalar, Polynomial<T>& other) {
    return other != scalar;
}


template <typename T>
ostream& operator<<(ostream& out, const Polynomial<T>& poly) {
    int deg = poly.Degree();
    T minus_one = T(0) - T(1);
    if (deg > 0) {
        if (deg == 1) {
            if (poly[deg] == minus_one) {
                out << "-x";
            } else if (poly[deg] == T(1)) {
                out << "x";
            }else if(poly[deg] < T(0)) {
                out << poly[deg] << "*" << "x";
            } else  if (poly[deg] > T(0)) {
                out << poly[deg] << "*" << "x";
            }
            deg--;
        } else {
            if (poly[deg] == minus_one) {
                out << "-x^" << deg;
            } else if (poly[deg] == T(1)) {
                out << "x^" << deg;
            }else {
                out << poly[deg] << "*" << "x^" << deg;
            }
            deg--;
        }
    } else {
        out << poly[deg];
        return out;
    }
    for (; deg >= 0; deg--) {
        if (deg > 1) {
            if (poly[deg] == minus_one) {
                out << "-x^" << deg;
            } else if (poly[deg] == T(1)) {
                out << "+" << "x^" << deg;
            } else if(poly[deg] < T(0)) {
                out << poly[deg] << "*" << "x^" << deg;
            } else  if (poly[deg] > T(0)) {
                out << "+" << poly[deg] << "*" << "x^" << deg;
            }
        } else if (deg == 1) {
            if (poly[deg] == minus_one) {
                out << "-x";
            } else if (poly[deg] == T(1)) {
                out << "+" << "x";
            }else if(poly[deg] < T(0)) {
                out << poly[deg] << "*" << "x";
            } else  if (poly[deg] > T(0)) {
                out << "+" << poly[deg] << "*" << "x";
            }
        } else {
            if (poly[deg] < T(0)) {
                out << poly[deg];
            } else if (poly[deg] > T(0)) {
                out << "+" << poly[deg];
            }
        }
    }
    return out;
}
