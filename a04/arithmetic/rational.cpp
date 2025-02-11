#include "rational.hpp"
#include <cstdint>
#include <print>

arithmetic::Rational::Rational() : numerator(0), denominator(1) {}

arithmetic::Rational::Rational(int64_t int_number) : numerator(int_number), denominator(1) {}

arithmetic::Rational::Rational(int64_t numerator, int64_t denominator) {
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    bool was_negative = false;
    if (numerator < 0) {
        numerator = -numerator;
        was_negative = true;
    }

    int64_t smaller_number = 0;
    int64_t bigger_number = 0;
    if (numerator > denominator) {
        bigger_number = numerator;
        smaller_number = denominator;
    } else {
        bigger_number = denominator;
        smaller_number = numerator;
    }

    int64_t biggest_divider = 0;
    for (int i = smaller_number; i > 0; i--) {
        if (smaller_number % i == 0 && bigger_number % i == 0) {
            biggest_divider = i;
            break;
        }
    }

    if (biggest_divider == 0) {
        this->numerator = numerator;
        this->denominator = denominator;
    } else {
        this->numerator = numerator / biggest_divider;
        this->denominator = denominator / biggest_divider;
    }
    if (was_negative) { this->numerator = -this->numerator; }
}

int64_t arithmetic::Rational::num() const { return numerator; }

int64_t arithmetic::Rational::den() const { return denominator; }

arithmetic::Rational::operator double() const {
    return static_cast<double>(numerator) / static_cast<double>(denominator);
}

arithmetic::Rational arithmetic::Rational::inv() const { return {denominator, numerator}; }

arithmetic::Rational arithmetic::Rational::operator-() const {
    arithmetic::Rational r = Rational(numerator, denominator);
    r.numerator = -r.numerator;
    return r;
}

arithmetic::Rational arithmetic::Rational::operator+() const {
    arithmetic::Rational r = Rational(numerator, denominator);
    return r;
}

arithmetic::Rational arithmetic::Rational::operator-(const arithmetic::Rational &r2) const {
    int64_t shared_denominator = this->denominator * r2.den();
    int64_t this_numerator = this->numerator * r2.den();
    int64_t r2_numerator = r2.num() * this->denominator;

    return {this_numerator - r2_numerator, shared_denominator};
}

arithmetic::Rational arithmetic::Rational::operator+(const arithmetic::Rational &r2) const {
    int64_t shared_denominator = this->denominator * r2.den();
    int64_t this_numerator = this->numerator * r2.den();
    int64_t r2_numerator = r2.num() * this->denominator;

    return {this_numerator + r2_numerator, shared_denominator};
}

arithmetic::Rational arithmetic::Rational::operator*(const arithmetic::Rational &r2) const {
    return {this->numerator * r2.num(), this->denominator * r2.den()};
}

arithmetic::Rational arithmetic::Rational::operator/(const arithmetic::Rational &r2) const {
    return {this->numerator * r2.den(), this->denominator * r2.num()};
}

std::strong_ordering arithmetic::Rational::operator<=>(const Rational &r2) const {
    int64_t lhs = this->numerator * r2.denominator;
    int64_t rhs = r2.numerator * this->denominator;
    return lhs <=> rhs;
}

bool arithmetic::Rational::operator==(const Rational &r2) const {
    return (this->numerator * r2.denominator) == (r2.numerator * this->denominator);
}
