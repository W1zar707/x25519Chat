// ecdh.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include "uint256.h"
#include "Fe25519.h"
UInt256 ScalarMult(UInt256& privateKey, const UInt256& point);
void cswap(Fe25519& R0, Fe25519& R1, unsigned int bit);