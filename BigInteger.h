
#ifndef __BIGINTEGER_H__
#define __BIGINTEGER_H__

#include <vector>

template <typename T = unsigned long long, T Base = (1ULL << 32)>
class BigInt {
public:
	typedef T BaseType;
	static const BaseType base = Base;
	
	BigInt(): sign(1) {}
	BigInt(BaseType value): sign((value < 0)? -1 : 1) {
		value = ((value < 0)? -value : value);
		while (value > base) {
			digits.push_back(value % base);
		
			if (value >= Base) {
				digits.push_back(value / base);
			}
			value /= base;
		}
	}
	BigInt(const BigInt& bigInt): sign(bigInt.sign), digits(bigInt.digits) {}
	~BigInt() {}
	
	BigInt& operator= (const BigInt& bigInt) {
		if (this != &bigInt) {
			sign = bigInt.sign;
			digits = bigInt.digits;
		}
		return *this;
	}
	
	bool operator< (const BigInt& bigInt) const {
		if (digits.size() == bigInt.digits.size()) {
			if (digits.size() == 0 || (digits[0] == 0 && bigInt.digits[0] == 0)) {
				return false;
			}
		}

		if (sign != bigInt.sign) {
			return (sign < 0);
		}

		if (digits.size() < bigInt.digits.size()) {
			return (sign > 0);
		} else if (bigInt.digits.size() < digits.size()) {
			return (sign < 0);
		}
		int i = int(digits.size()) - 1;

		while (i > -1) {
			if (digits[i] < bigInt.digits[i]) {
				return (sign > 0);
			} else if (bigInt.digits[i] < digits[i]) {
				return (sign < 0);
			}
			--i;
		}
		return false;
	}

	BigInt& operator+= (BaseType value) {
		return *this;
	}
	
	BigInt& operator-= (BaseType value) {
		return *this;
	}
	
	BigInt& operator*= (BaseType value) {
		return *this;
	}
	
	BigInt& operator/= (BaseType value) {
		return *this;
	}

	BigInt& operator%= (BaseType value) {
		return *this;
	}

	BigInt& operator+= (const BigInt& value) {
		return *this;
	}
	
	BigInt& operator-= (const BigInt& value) {
		return *this;
	}
	
	BigInt& operator*= (const BigInt& value) {
		return *this;
	}
	
	BigInt& operator/= (const BigInt& value) {
		return *this;
	}
	
	BigInt& operator%= (const BigInt& value) {
		return *this;
	}

	BigInt operator+ (BaseType value) const {
		return *this;
	}
	
	BigInt operator- (BaseType value) const {
		return *this;
	}
	
	BigInt operator* (BaseType value) const {
		return *this;
	}
	
	BigInt operator/ (BaseType value) const {
		return *this;
	}

	BigInt operator% (BaseType value) const {
		return *this;
	}

	BigInt operator+ (const BigInt& value) const {
		return *this;
	}
	
	BigInt operator- (const BigInt& value) const {
		return *this;
	}
	
	BigInt operator* (const BigInt& value) const {
		return *this;
	}
	
	BigInt operator/ (const BigInt& value) const {
		return *this;
	}
	
	BigInt operator% (const BigInt& value) const {
		return *this;
	}

	BigInt exp(BaseType value) const {
		return *this;
	}

	BigInt exp(const BigInt& value) const {
		return *this;
	}

	BigInt expmod(BaseType value, BaseType mod) const {
		return *this;
	}

	BigInt expmod(const BigInt& value, BaseType mod) const {
		return *this;
	}

	BigInt expmod(const BigInt& value, const BigInt& mod) const {
		return *this;
	}

	BigInt mulmod(BaseType value, BaseType mod) const {
		return *this;
	}

	BigInt mulmod(const BigInt& value, BaseType mod) const {
		return *this;
	}

	BigInt mulmod(const BigInt& value, const BigInt& mod) const {
		return *this;
	}

	BigInt gcd(BaseType value) const {
		return *this;
	}

	BigInt gcd(const BigInt& value) const {
		return *this;
	}

	BigInt sqrt() const {
		return *this;
	}

private:
	BaseType sign;
	std::vector<BaseType> digits;
};

#endif // __BIGINTEGER_H__
