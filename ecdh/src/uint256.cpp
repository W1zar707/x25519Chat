#include "uint256.h"
UInt256::~UInt256() {
    SecureZeroMemory(key, sizeof(key));
}
UInt256 UInt256::generateKey() {
    UInt256 out = UInt256();
    NTSTATUS status = BCryptGenRandom(NULL, out.key, 32, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    if (status != STATUS_SUCCESS) {
        throw std::runtime_error("BCryptGenRandom failed");
    }
    out.key[0] &= 248; // Делает скаляр кратным 8 (cofactor clearing)

    out.key[31] &= 127; // Гарантирует scalar < 2^255,
    // чтобы не выйти за пределы поля

    out.key[31] |= 64; // Фиксирует бит 254, обеспечивая
    // константное время выполнения ladder
    return out;
}
UInt256::operator std::string() const {
    std::string result;
    for (int i = 0; i < 32; i++) {
        char buf[3];
        snprintf(buf, sizeof(buf), "%02X", key[i]);
        result += buf;
        result += ":";
    }
    return result;
}
UInt256 UInt256::basePoint() {
    UInt256 result = UInt256();
    result.key[0] = 9;
    
    return result;
}
UInt256::UInt256(Fe25519& other) {
    Fe25519 tmp = other;
    tmp.carry(); tmp.carry(); tmp.carry();
    const int64_t kBottom25Bits = 0x1ffffffLL;
    const int64_t kBottom26Bits = 0x3ffffffLL;
    int64_t h0 = tmp.value[0];
    int64_t h1 = tmp.value[1];
    int64_t h2 = tmp.value[2];
    int32_t h3 = tmp.value[3];
    int64_t h4 = tmp.value[4];
    int64_t h5 = tmp.value[5];
    int64_t h6 = tmp.value[6];
    int64_t h7 = tmp.value[7];
    int64_t h8 = tmp.value[8];
    int64_t h9 = tmp.value[9];
    int64_t q;

    q = (19 * h9 + (((int64_t)1) << 24)) >> 25;
    q = (h0 + q) >> 26;
    q = (h1 + q) >> 25;
    q = (h2 + q) >> 26;
    q = (h3 + q) >> 25;
    q = (h4 + q) >> 26;
    q = (h5 + q) >> 25;
    q = (h6 + q) >> 26;
    q = (h7 + q) >> 25;
    q = (h8 + q) >> 26;
    q = (h9 + q) >> 25;

    /* Goal: Output h-(2^255-19)q, which is between 0 and 2^255-20. */
    h0 += 19 * q;
    /* Goal: Output h-2^255 q, which is between 0 and 2^255-20. */

    h1 += h0 >> 26;
    h0 &= kBottom26Bits;
    h2 += h1 >> 25;
    h1 &= kBottom25Bits;
    h3 += h2 >> 26;
    h2 &= kBottom26Bits;
    h4 += h3 >> 25;
    h3 &= kBottom25Bits;
    h5 += h4 >> 26;
    h4 &= kBottom26Bits;
    h6 += h5 >> 25;
    h5 &= kBottom25Bits;
    h7 += h6 >> 26;
    h6 &= kBottom26Bits;
    h8 += h7 >> 25;
    h7 &= kBottom25Bits;
    h9 += h8 >> 26;
    h8 &= kBottom26Bits;
    h9 &= kBottom25Bits;
    /* h10 = carry9 */

    /*
     * Goal: Output h0+...+2^255 h10-2^255 q, which is between 0 and 2^255-20.
     * Have h0+...+2^230 h9 between 0 and 2^255-1;
     * evidently 2^255 h10-2^255 q = 0.
     * Goal: Output h0+...+2^230 h9.
     */
    this->key[0] = (uint8_t)(h0 >> 0);
    this->key[1] = (uint8_t)(h0 >> 8);
    this->key[2] = (uint8_t)(h0 >> 16);
    this->key[3] = (uint8_t)((h0 >> 24) | ((uint64_t)(h1) << 2));
    this->key[4] = (uint8_t)(h1 >> 6);
    this->key[5] = (uint8_t)(h1 >> 14);
    this->key[6] = (uint8_t)((h1 >> 22) | ((uint64_t)(h2) << 3));
    this->key[7] = (uint8_t)(h2 >> 5);
    this->key[8] = (uint8_t)(h2 >> 13);
    this->key[9] = (uint8_t)((h2 >> 21) | ((uint64_t)(h3) << 5));
    this->key[10] = (uint8_t)(h3 >> 3);
    this->key[11] = (uint8_t)(h3 >> 11);
    this->key[12] = (uint8_t)((h3 >> 19) | ((uint64_t)(h4) << 6));
    this->key[13] = (uint8_t)(h4 >> 2);
    this->key[14] = (uint8_t)(h4 >> 10);
    this->key[15] = (uint8_t)(h4 >> 18);
    this->key[16] = (uint8_t)(h5 >> 0);
    this->key[17] = (uint8_t)(h5 >> 8);
    this->key[18] = (uint8_t)(h5 >> 16);
    this->key[19] = (uint8_t)((h5 >> 24) | ((uint64_t)(h6) << 1));
    this->key[20] = (uint8_t)(h6 >> 7);
    this->key[21] = (uint8_t)(h6 >> 15);
    this->key[22] = (uint8_t)((h6 >> 23) | ((uint64_t)(h7) << 3));
    this->key[23] = (uint8_t)(h7 >> 5);
    this->key[24] = (uint8_t)(h7 >> 13);
    this->key[25] = (uint8_t)((h7 >> 21) | ((uint64_t)(h8) << 4));
    this->key[26] = (uint8_t)(h8 >> 4);
    this->key[27] = (uint8_t)(h8 >> 12);
    this->key[28] = (uint8_t)((h8 >> 20) | ((uint64_t)(h9) << 6));
    this->key[29] = (uint8_t)(h9 >> 2);
    this->key[30] = (uint8_t)(h9 >> 10);
    this->key[31] = (uint8_t)(h9 >> 18);
}