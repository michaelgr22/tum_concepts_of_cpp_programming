#include "complex.hpp"
#include <cmath>

arithmetic::Complex::Complex() : _real(0.0), _image(0.0) {}

arithmetic::Complex::Complex(double real) : _real(real), _image(0.0) {}

arithmetic::Complex::Complex(double real, double image) : _real(real), _image(image) {}

double arithmetic::Complex::real() const { return _real; }

double arithmetic::Complex::imag() const { return _image; }

double arithmetic::Complex::abs() const { return sqrt(pow(_real, 2) + pow(_image, 2)); }

double arithmetic::Complex::norm() const { return pow(_real, 2) + pow(_image, 2); }

double arithmetic::Complex::arg() const { return atan2(_image, _real); }

arithmetic::Complex arithmetic::Complex::conj() const { return {_real, -_image}; }

arithmetic::Complex arithmetic::Complex::operator-() const { return {-_real, -_image}; }

arithmetic::Complex arithmetic::Complex::operator+() const { return {_real, _image}; }

arithmetic::Complex arithmetic::Complex::operator-(const Complex &c2) const {
    return {_real - c2.real(), _image - c2.imag()};
}

arithmetic::Complex arithmetic::Complex::operator+(const Complex &c2) const {
    return {_real + c2.real(), _image + c2.imag()};
}

arithmetic::Complex arithmetic::Complex::operator*(const Complex &c2) const {
    double real = _real * c2.real() - _image * c2.imag();
    double image = _real * c2.imag() + _image * c2.real();
    return {real, image};
}

arithmetic::Complex arithmetic::Complex::operator/(const Complex &c2) const {
    double real = (_real * c2.real() + _image * c2.imag()) / (pow(c2.real(), 2) + pow(c2.imag(), 2));
    double image = (_image * c2.real() - _real * c2.imag()) / (pow(c2.real(), 2) + pow(c2.imag(), 2));
    return {real, image};
}

bool arithmetic::Complex::operator==(const Complex &r2) const {
    if (_real == r2.real() && _image == r2.imag()) { return true; }
    return false;
}