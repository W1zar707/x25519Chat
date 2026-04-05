#pragma once
#include <string>
struct UInt256;
struct Fe25519 {
	int64_t value[10] {0};
    Fe25519(const UInt256& scalar);
	Fe25519() = default;
	Fe25519 operator+(const Fe25519& other);
	Fe25519 operator-(const Fe25519& other);
	Fe25519 operator*(const Fe25519& other);
	Fe25519 square();
	Fe25519 nsquare(int exponent);
	Fe25519 inverse();
	Fe25519 mul_a24();
	operator std::string() const;
	void carry();
	static Fe25519 One();
	static Fe25519 Zero();
};

