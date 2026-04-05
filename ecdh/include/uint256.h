#pragma once
#include <iostream>
#include <windows.h>
#include <bcrypt.h>
#include <ntstatus.h>
#include <stdexcept>
#include "Fe25519.h"
struct UInt256 {
	uint8_t key[32]{0};
	UInt256() = default;
	~UInt256();
	static UInt256 generateKey();
	operator std::string() const;
	static UInt256 basePoint();
	UInt256(Fe25519& other);
};