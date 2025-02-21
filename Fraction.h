
#ifndef __FRACTION_H__
#define __FRACTION_H__

#include <cassert>
#include <string>
#include <sstream>

template <typename T>
class Fraction {

public:
	Fraction(): a(0), b(1) {}
	Fraction(T numerator, T denominator): a(numerator), b(denominator) {
		assert (b != 0);

		if (a == 0) {
			b = 1;
		} else if ((a < 0 && b < 0) || (a > 0 && b < 0)) {
			a *= -1;
			b *= -1;
		}
	}
	Fraction(const std::string& s): a(0), b(1) {
		int plus = 0, minus = 0, slash = 0, dot = 0;
		std::ostringstream oss;
		int n = int(s.length());
		int i = 0;
		const std::string& validChars = "+-/.0123456789";
		
		while (i < n) {
			if (validChars.find(s[i]) != std::string::npos) {
				oss << s[i];
				plus += (s[i] == '+');
				minus += (s[i] == '-');
				slash += (s[i] == '/');
				dot += (s[i] == '.');
			} else if (!isspace(s[i])) {
				return;
			}
			++i;
		}
		
		if ((plus + minus == 0 || plus + minus == 1) && (slash + dot == 0 || slash + dot == 1)) {
			std::string str = oss.str();
			
			if (str.empty() || (plus && str[0] != '+') || (minus && str[0] != '-')) {
				return;
			}
			
			if (plus || minus) {
				str = str.substr(1);
			}

			if (slash) {
				if (str[0] != '/' && str[str.length() - 1] != '/') {
					{
						std::istringstream iss(str.substr(0, slash));
						iss >> a;
					}
					{
						std::istringstream iss(str.substr(slash + 1));
						iss >> b;
					}
					reduce();
				
					if (minus) {
						a = -a;
					}
				}
			} else if (dot) {
				int pdot = int(str.find('.'));
				std::istringstream iss(str.substr(0, pdot) + ((pdot < int(str.length()) - 1)? str.substr(pdot + 1) : ""));
				iss >> a;
				
				for (int p = 1; p < int(str.length()) - pdot; ++p) {
					b *= 10;
				}
				reduce();
				
				if (minus) {
					a = -a;
				}
			} else {
				std::istringstream iss(str);
				iss >> a;
				
				if (minus) {
					a = -a;
				}
			}
		}
	}
	~Fraction() {}

	inline bool operator< (const Fraction& f) const {
		return (a * f.b < b * f.a);
	}

	inline const T& Numerator() const { return a; }
	inline const T& Denominator() const { return b; }
	
	inline Fraction& operator+= (const Fraction& f) {
		T t = lcm(b, f.b);
		a = a * (t / b) + f.a * (t / f.b);
		b = t;
		reduce();
		return *this;
	}

	inline Fraction operator+ (const Fraction& f) const {
		Fraction g(*this);
		g += f;
		return g;
	}

	inline Fraction& operator-= (const Fraction& f) {
		T t = lcm(b, f.b);
		a = a * (t / b) - f.a * (t / f.b);
		b = t;
		reduce();
		return *this;
	}

	inline Fraction operator- (const Fraction& f) const {
		Fraction g(*this);
		g -= f;
		return g;
	}

	inline Fraction& operator*= (const Fraction& f) {
		T t1 = gcd((a > 0)? a : -a, f.b);
		T t2 = gcd((f.a > 0)? f.a : -f.a, b);
		a = (a / t1) * (f.a / t2);
		b = (b / t2) * (f.b / t1);
		return *this;
	}

	inline Fraction operator* (const Fraction& f) const {
		Fraction g(*this);
		g *= f;
		return g;
	}

	inline Fraction& operator/= (const Fraction& f) {
		assert (f.a != 0);
		*this *= Fraction(f.Denominator(), f.Numerator());
		return *this;
	}

	inline Fraction operator/ (const Fraction& f) const {
		Fraction g(*this);
		g /= f;
		return g;
	}

	inline std::string ToString() const {
		std::ostringstream oss;
		oss << a << '/' << b;
		return oss.str();
	}

	inline operator std::string() const {
		return ToString();
	}

protected:
	static T gcd(T x, T y) {
		if (y == 0) {
			return x;
		}
		return gcd(y, x % y);
	}

	static inline T lcm(T x, T y) {
		return (x * y) / gcd(x, y);
	}

	inline void reduce() {
		T t = gcd((a > 0)? a : -a, b);
		a /= t;
		b /= t;
	}

private:
	T a, b; // a / b

};

#endif // __FRACTION_H__
