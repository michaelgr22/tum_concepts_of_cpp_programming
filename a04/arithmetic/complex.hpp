#pragma once

namespace arithmetic {
/// A complex number
///
/// A number of the form z = x + iy
class Complex {
private:
    double _real;
    double _image;

public:
    /// Default constructor - the zero value.
    Complex();
    /// Construct a complex number with only a real component.
    /// @param real The real component.
    Complex(double real);
    ///  Construct a complex number from a real and an imaginary component.
    /// @param real The real component.
    /// @param image The imaginary component.
    Complex(double real, double image);

    /// Real component of the number.
    /// @return The real component as a double.
    double real() const;
    /// Imaginary component of the number.
    /// @return The coefficient of the imaginary component of the number.
    double imag() const;

    /// The absolute value, or modulus, of the complex number.
    ///
    /// This is equivalent to the distance of the number from zero on the complex plane.
    /// @return The absolute value of the number.
    double abs() const;
    /// The field norm of the number.
    ///
    /// The field norm of a complex number is defined as the sum of the squares of its coefficients.
    /// @return The value of the field norm of the number.
    double norm() const;
    /// The argument, or phase, of the complex number, in radians.
    ///
    /// This is the angle of the number with the positive real axis on the complex plane.
    /// @return The argument (in radians) of the number.
    double arg() const;

    /// The complex conjugate.
    ///
    /// This is the reflection of the number about the real axis on the complex plane.
    /// @return The complex conjugate of the number.
    Complex conj() const;

    /// Negate the number.
    ///
    /// This is the reflection of the number about the zero point of the complex plane.
    /// @return The negation of the number.
    Complex operator-() const;
    /// Unary plus
    ///
    /// This is a no-op.
    /// @return The same number.
    Complex operator+() const;

    /// Subtract another complex number.
    /// @param other The number to subtract.
    /// @return The result of subtracting this number from the other.
    Complex operator-(const Complex &c2) const;
    /// Add another complex number.
    /// @param other The number to add.
    /// @return The result of adding this number from the other.
    Complex operator+(const Complex &c2) const;
    /// Multiply by another complex number.
    /// @param other The number by which to multiply.
    /// @return The result of multiplying this number by the other.
    Complex operator*(const Complex &c2) const;
    /// Divide by another complex number.
    ///
    /// Dividing by zero is undefined behavior.
    /// @param other The number to divide by.
    /// @return The result of dividing this number by the other.
    Complex operator/(const Complex &c2) const;

    /// Compare another complex number for equality.
    /// @param other Number to compare to.
    /// @return True if this is equal to other; otherwise, false.
    bool operator==(const Complex &r2) const;
};
} // namespace arithmetic