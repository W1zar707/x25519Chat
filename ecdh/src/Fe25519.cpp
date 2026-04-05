#include "UInt256.h"
#include "Fe25519.h"
#include <iostream>

using namespace std;
static uint64_t load_3(const uint8_t* in)
{
    uint64_t result;

    result = ((uint64_t)in[0]);
    result |= ((uint64_t)in[1]) << 8;
    result |= ((uint64_t)in[2]) << 16;
    return result;
}

static uint64_t load_4(const uint8_t* in)
{
    uint64_t result;

    result = ((uint64_t)in[0]);
    result |= ((uint64_t)in[1]) << 8;
    result |= ((uint64_t)in[2]) << 16;
    result |= ((uint64_t)in[3]) << 24;
    return result;
}
Fe25519::Fe25519(const UInt256& scalar) {
    const uint8_t* s = scalar.key;
    int64_t h0 = load_4(s);
    int64_t h1 = load_3(s + 4) << 6;
    int64_t h2 = load_3(s + 7) << 5;
    int64_t h3 = load_3(s + 10) << 3;
    int64_t h4 = load_3(s + 13) << 2;
    int64_t h5 = load_4(s + 16);
    int64_t h6 = load_3(s + 20) << 7;
    int64_t h7 = load_3(s + 23) << 5;
    int64_t h8 = load_3(s + 26) << 4;
    int64_t h9 = (load_3(s + 29) & 0x7fffff) << 2;
    value[0] = (int64_t)h0;
    value[1] = (int64_t)h1;
    value[2] = (int64_t)h2;
    value[3] = (int64_t)h3;
    value[4] = (int64_t)h4;
    value[5] = (int64_t)h5;
    value[6] = (int64_t)h6;
    value[7] = (int64_t)h7;
    value[8] = (int64_t)h8;
    value[9] = (int64_t)h9;
    carry(); carry(); carry();
}
Fe25519 Fe25519::square() {    
    int32_t f0 = this->value[0];
    int32_t f1 = this->value[1];
    int32_t f2 = this->value[2];
    int32_t f3 = this->value[3];
    int32_t f4 = this->value[4];
    int32_t f5 = this->value[5];
    int32_t f6 = this->value[6];
    int32_t f7 = this->value[7];
    int32_t f8 = this->value[8];
    int32_t f9 = this->value[9];
    int32_t f0_2 = 2 * f0;
    int32_t f1_2 = 2 * f1;
    int32_t f2_2 = 2 * f2;
    int32_t f3_2 = 2 * f3;
    int32_t f4_2 = 2 * f4;
    int32_t f5_2 = 2 * f5;
    int32_t f6_2 = 2 * f6;
    int32_t f7_2 = 2 * f7;
    int32_t f5_38 = 38 * f5; /* 1.959375*2^30 */
    int32_t f6_19 = 19 * f6; /* 1.959375*2^30 */
    int32_t f7_38 = 38 * f7; /* 1.959375*2^30 */
    int32_t f8_19 = 19 * f8; /* 1.959375*2^30 */
    int32_t f9_38 = 38 * f9; /* 1.959375*2^30 */
    int64_t f0f0 = f0 * (int64_t)f0;
    int64_t f0f1_2 = f0_2 * (int64_t)f1;
    int64_t f0f2_2 = f0_2 * (int64_t)f2;
    int64_t f0f3_2 = f0_2 * (int64_t)f3;
    int64_t f0f4_2 = f0_2 * (int64_t)f4;
    int64_t f0f5_2 = f0_2 * (int64_t)f5;
    int64_t f0f6_2 = f0_2 * (int64_t)f6;
    int64_t f0f7_2 = f0_2 * (int64_t)f7;
    int64_t f0f8_2 = f0_2 * (int64_t)f8;
    int64_t f0f9_2 = f0_2 * (int64_t)f9;
    int64_t f1f1_2 = f1_2 * (int64_t)f1;
    int64_t f1f2_2 = f1_2 * (int64_t)f2;
    int64_t f1f3_4 = f1_2 * (int64_t)f3_2;
    int64_t f1f4_2 = f1_2 * (int64_t)f4;
    int64_t f1f5_4 = f1_2 * (int64_t)f5_2;
    int64_t f1f6_2 = f1_2 * (int64_t)f6;
    int64_t f1f7_4 = f1_2 * (int64_t)f7_2;
    int64_t f1f8_2 = f1_2 * (int64_t)f8;
    int64_t f1f9_76 = f1_2 * (int64_t)f9_38;
    int64_t f2f2 = f2 * (int64_t)f2;
    int64_t f2f3_2 = f2_2 * (int64_t)f3;
    int64_t f2f4_2 = f2_2 * (int64_t)f4;
    int64_t f2f5_2 = f2_2 * (int64_t)f5;
    int64_t f2f6_2 = f2_2 * (int64_t)f6;
    int64_t f2f7_2 = f2_2 * (int64_t)f7;
    int64_t f2f8_38 = f2_2 * (int64_t)f8_19;
    int64_t f2f9_38 = f2 * (int64_t)f9_38;
    int64_t f3f3_2 = f3_2 * (int64_t)f3;
    int64_t f3f4_2 = f3_2 * (int64_t)f4;
    int64_t f3f5_4 = f3_2 * (int64_t)f5_2;
    int64_t f3f6_2 = f3_2 * (int64_t)f6;
    int64_t f3f7_76 = f3_2 * (int64_t)f7_38;
    int64_t f3f8_38 = f3_2 * (int64_t)f8_19;
    int64_t f3f9_76 = f3_2 * (int64_t)f9_38;
    int64_t f4f4 = f4 * (int64_t)f4;
    int64_t f4f5_2 = f4_2 * (int64_t)f5;
    int64_t f4f6_38 = f4_2 * (int64_t)f6_19;
    int64_t f4f7_38 = f4 * (int64_t)f7_38;
    int64_t f4f8_38 = f4_2 * (int64_t)f8_19;
    int64_t f4f9_38 = f4 * (int64_t)f9_38;
    int64_t f5f5_38 = f5 * (int64_t)f5_38;
    int64_t f5f6_38 = f5_2 * (int64_t)f6_19;
    int64_t f5f7_76 = f5_2 * (int64_t)f7_38;
    int64_t f5f8_38 = f5_2 * (int64_t)f8_19;
    int64_t f5f9_76 = f5_2 * (int64_t)f9_38;
    int64_t f6f6_19 = f6 * (int64_t)f6_19;
    int64_t f6f7_38 = f6 * (int64_t)f7_38;
    int64_t f6f8_38 = f6_2 * (int64_t)f8_19;
    int64_t f6f9_38 = f6 * (int64_t)f9_38;
    int64_t f7f7_38 = f7 * (int64_t)f7_38;
    int64_t f7f8_38 = f7_2 * (int64_t)f8_19;
    int64_t f7f9_76 = f7_2 * (int64_t)f9_38;
    int64_t f8f8_19 = f8 * (int64_t)f8_19;
    int64_t f8f9_38 = f8 * (int64_t)f9_38;
    int64_t f9f9_38 = f9 * (int64_t)f9_38;
    int64_t h0 = f0f0 + f1f9_76 + f2f8_38 + f3f7_76 + f4f6_38 + f5f5_38;
    int64_t h1 = f0f1_2 + f2f9_38 + f3f8_38 + f4f7_38 + f5f6_38;
    int64_t h2 = f0f2_2 + f1f1_2 + f3f9_76 + f4f8_38 + f5f7_76 + f6f6_19;
    int64_t h3 = f0f3_2 + f1f2_2 + f4f9_38 + f5f8_38 + f6f7_38;
    int64_t h4 = f0f4_2 + f1f3_4 + f2f2 + f5f9_76 + f6f8_38 + f7f7_38;
    int64_t h5 = f0f5_2 + f1f4_2 + f2f3_2 + f6f9_38 + f7f8_38;
    int64_t h6 = f0f6_2 + f1f5_4 + f2f4_2 + f3f3_2 + f7f9_76 + f8f8_19;
    int64_t h7 = f0f7_2 + f1f6_2 + f2f5_2 + f3f4_2 + f8f9_38;
    int64_t h8 = f0f8_2 + f1f7_4 + f2f6_2 + f3f5_4 + f4f4 + f9f9_38;
    int64_t h9 = f0f9_2 + f1f8_2 + f2f7_2 + f3f6_2 + f4f5_2;

    Fe25519 out;

    out.value[0] = h0; out.value[1] = h1; out.value[2] = h2; out.value[3] = h3; out.value[4] = h4;
    out.value[5] = h5; out.value[6] = h6; out.value[7] = h7; out.value[8] = h8; out.value[9] = h9;
    out.carry();
    out.carry();
    out.carry();
    return out;
}
Fe25519 Fe25519::nsquare(int exponent) {
    Fe25519 result;
    result = this->square();
    for (int i = 1; i < exponent; ++i) {
        result = result.square();
    }
    result.carry(); result.carry(); result.carry();
    return result;
}
Fe25519 Fe25519::inverse() {
    int i;
    Fe25519 z = *this;
    /* t0 = z ** 2 */
    Fe25519 t0 = z.square();
    /* t1 = t0 ** (2 ** 2) = z ** 8 */
    Fe25519 t1 = t0.square();
    t1 = t1.square();
    /* t1 = z * t1 = z ** 9 */
    t1 = z * t1;
    /* t0 = t0 * t1 = z ** 11 */
    t0 = t0 * t1;
    /* t2 = t0 ** 2 = z ** 22 */
    Fe25519 t2 = t0.square();
    /* t1 = t1 * t2 = z ** (2 ** 5 - 1) */
    t1 = t1 * t2;
    /* t2 = t1 ** (2 ** 5) = z ** ((2 ** 5) * (2 ** 5 - 1)) */
    t2 = t1.square();
    for (i = 1; i < 5; ++i) {
        t2 = t2.square();
    }
    /* t1 = z ** (2 ** 10 - 1) */
    t1 = t2 * t1;

    /* t2 = z ** (2 ** 20 - 1) */
    t2 = t1.square();
    for (i = 1; i < 10; ++i) {
        t2 = t2.square();
    }
    t2 = t2 * t1;

    /* t3 = z ** (2 ** 40 - 1) */
    Fe25519 t3 = t2.square();
    for (i = 1; i < 20; ++i) {
        t3 = t3.square();
    }
    t2 = t3 * t2;

    /* t2 = z ** (2 ** 10) * (2 ** 40 - 1) */
    for (i = 0; i < 10; ++i) {
        t2 = t2.square();
    }
    /* t1 = z ** (2 ** 50 - 1) */
    t1 = t2 * t1;

    /* t2 = z ** (2 ** 100 - 1) */
    t2 = t1.square();
    for (i = 1; i < 50; ++i) {
        t2 = t2.square();
    }
    t2 = t2 * t1;

    /* t3 = z ** (2 ** 200 - 1) */
    t3 = t2.square();
    for (i = 1; i < 100; ++i) {
        t3 = t3.square();
    }
    t2 = t3 * t2;

    /* t2 = z ** ((2 ** 50) * (2 ** 200 - 1)) */
    t2 = t2.square();
    for (i = 1; i < 50; ++i) {
        t2 = t2.square();
    }
    /* t1 = z ** (2 ** 250 - 1) */
    t1 = t2 * t1;

    /* t1 = z ** ((2 ** 5) * (2 ** 250 - 1)) */
    t1 = t1.square();
    for (i = 1; i < 5; ++i) {
        t1 = t1.square();
    }

    /* Recall t0 = z ** 11; out = z ** (2 ** 255 - 21) */
    Fe25519 out = t1 * t0;
    return out;
}
Fe25519 Fe25519::mul_a24() {
    Fe25519 result;
    for (int i = 0; i < 10; ++i) {
        result.value[i] = this->value[i] * (int64_t)121665;
    }
    result.carry(); result.carry(); result.carry();
    return result;
}
Fe25519 Fe25519::operator+(const Fe25519& other) {
    Fe25519 out = Fe25519();
    for (int i = 0; i < 10; ++i) {
        out.value[i] = this->value[i] + other.value[i];
    }
    return out;
}
Fe25519 Fe25519::operator-(const Fe25519& other) {
    Fe25519 out = Fe25519();
    for (int i = 0; i < 10; i++) {
        out.value[i] = value[i] - other.value[i];
    }
    out.carry(); out.carry(); out.carry();
    return out;
}
Fe25519 Fe25519::operator*(const Fe25519& other) {
    
    int32_t f0 = this->value[0];
    int32_t f1 = this->value[1];
    int32_t f2 = this->value[2];
    int32_t f3 = this->value[3];
    int32_t f4 = this->value[4];
    int32_t f5 = this->value[5];
    int32_t f6 = this->value[6];
    int32_t f7 = this->value[7];
    int32_t f8 = this->value[8];
    int32_t f9 = this->value[9];
    int32_t g0 = other.value[0];
    int32_t g1 = other.value[1];
    int32_t g2 = other.value[2];
    int32_t g3 = other.value[3];
    int32_t g4 = other.value[4];
    int32_t g5 = other.value[5];
    int32_t g6 = other.value[6];
    int32_t g7 = other.value[7];
    int32_t g8 = other.value[8];
    int32_t g9 = other.value[9];
    int32_t g1_19 = 19 * g1; /* 1.959375*2^29 */
    int32_t g2_19 = 19 * g2; /* 1.959375*2^30; still ok */
    int32_t g3_19 = 19 * g3;
    int32_t g4_19 = 19 * g4;
    int32_t g5_19 = 19 * g5;
    int32_t g6_19 = 19 * g6;
    int32_t g7_19 = 19 * g7;
    int32_t g8_19 = 19 * g8;
    int32_t g9_19 = 19 * g9;
    int32_t f1_2 = 2 * f1;
    int32_t f3_2 = 2 * f3;
    int32_t f5_2 = 2 * f5;
    int32_t f7_2 = 2 * f7;
    int32_t f9_2 = 2 * f9;
    int64_t f0g0 = f0 * (int64_t)g0;
    int64_t f0g1 = f0 * (int64_t)g1;
    int64_t f0g2 = f0 * (int64_t)g2;
    int64_t f0g3 = f0 * (int64_t)g3;
    int64_t f0g4 = f0 * (int64_t)g4;
    int64_t f0g5 = f0 * (int64_t)g5;
    int64_t f0g6 = f0 * (int64_t)g6;
    int64_t f0g7 = f0 * (int64_t)g7;
    int64_t f0g8 = f0 * (int64_t)g8;
    int64_t f0g9 = f0 * (int64_t)g9;
    int64_t f1g0 = f1 * (int64_t)g0;
    int64_t f1g1_2 = f1_2 * (int64_t)g1;
    int64_t f1g2 = f1 * (int64_t)g2;
    int64_t f1g3_2 = f1_2 * (int64_t)g3;
    int64_t f1g4 = f1 * (int64_t)g4;
    int64_t f1g5_2 = f1_2 * (int64_t)g5;
    int64_t f1g6 = f1 * (int64_t)g6;
    int64_t f1g7_2 = f1_2 * (int64_t)g7;
    int64_t f1g8 = f1 * (int64_t)g8;
    int64_t f1g9_38 = f1_2 * (int64_t)g9_19;
    int64_t f2g0 = f2 * (int64_t)g0;
    int64_t f2g1 = f2 * (int64_t)g1;
    int64_t f2g2 = f2 * (int64_t)g2;
    int64_t f2g3 = f2 * (int64_t)g3;
    int64_t f2g4 = f2 * (int64_t)g4;
    int64_t f2g5 = f2 * (int64_t)g5;
    int64_t f2g6 = f2 * (int64_t)g6;
    int64_t f2g7 = f2 * (int64_t)g7;
    int64_t f2g8_19 = f2 * (int64_t)g8_19;
    int64_t f2g9_19 = f2 * (int64_t)g9_19;
    int64_t f3g0 = f3 * (int64_t)g0;
    int64_t f3g1_2 = f3_2 * (int64_t)g1;
    int64_t f3g2 = f3 * (int64_t)g2;
    int64_t f3g3_2 = f3_2 * (int64_t)g3;
    int64_t f3g4 = f3 * (int64_t)g4;
    int64_t f3g5_2 = f3_2 * (int64_t)g5;
    int64_t f3g6 = f3 * (int64_t)g6;
    int64_t f3g7_38 = f3_2 * (int64_t)g7_19;
    int64_t f3g8_19 = f3 * (int64_t)g8_19;
    int64_t f3g9_38 = f3_2 * (int64_t)g9_19;
    int64_t f4g0 = f4 * (int64_t)g0;
    int64_t f4g1 = f4 * (int64_t)g1;
    int64_t f4g2 = f4 * (int64_t)g2;
    int64_t f4g3 = f4 * (int64_t)g3;
    int64_t f4g4 = f4 * (int64_t)g4;
    int64_t f4g5 = f4 * (int64_t)g5;
    int64_t f4g6_19 = f4 * (int64_t)g6_19;
    int64_t f4g7_19 = f4 * (int64_t)g7_19;
    int64_t f4g8_19 = f4 * (int64_t)g8_19;
    int64_t f4g9_19 = f4 * (int64_t)g9_19;
    int64_t f5g0 = f5 * (int64_t)g0;
    int64_t f5g1_2 = f5_2 * (int64_t)g1;
    int64_t f5g2 = f5 * (int64_t)g2;
    int64_t f5g3_2 = f5_2 * (int64_t)g3;
    int64_t f5g4 = f5 * (int64_t)g4;
    int64_t f5g5_38 = f5_2 * (int64_t)g5_19;
    int64_t f5g6_19 = f5 * (int64_t)g6_19;
    int64_t f5g7_38 = f5_2 * (int64_t)g7_19;
    int64_t f5g8_19 = f5 * (int64_t)g8_19;
    int64_t f5g9_38 = f5_2 * (int64_t)g9_19;
    int64_t f6g0 = f6 * (int64_t)g0;
    int64_t f6g1 = f6 * (int64_t)g1;
    int64_t f6g2 = f6 * (int64_t)g2;
    int64_t f6g3 = f6 * (int64_t)g3;
    int64_t f6g4_19 = f6 * (int64_t)g4_19;
    int64_t f6g5_19 = f6 * (int64_t)g5_19;
    int64_t f6g6_19 = f6 * (int64_t)g6_19;
    int64_t f6g7_19 = f6 * (int64_t)g7_19;
    int64_t f6g8_19 = f6 * (int64_t)g8_19;
    int64_t f6g9_19 = f6 * (int64_t)g9_19;
    int64_t f7g0 = f7 * (int64_t)g0;
    int64_t f7g1_2 = f7_2 * (int64_t)g1;
    int64_t f7g2 = f7 * (int64_t)g2;
    int64_t f7g3_38 = f7_2 * (int64_t)g3_19;
    int64_t f7g4_19 = f7 * (int64_t)g4_19;
    int64_t f7g5_38 = f7_2 * (int64_t)g5_19;
    int64_t f7g6_19 = f7 * (int64_t)g6_19;
    int64_t f7g7_38 = f7_2 * (int64_t)g7_19;
    int64_t f7g8_19 = f7 * (int64_t)g8_19;
    int64_t f7g9_38 = f7_2 * (int64_t)g9_19;
    int64_t f8g0 = f8 * (int64_t)g0;
    int64_t f8g1 = f8 * (int64_t)g1;
    int64_t f8g2_19 = f8 * (int64_t)g2_19;
    int64_t f8g3_19 = f8 * (int64_t)g3_19;
    int64_t f8g4_19 = f8 * (int64_t)g4_19;
    int64_t f8g5_19 = f8 * (int64_t)g5_19;
    int64_t f8g6_19 = f8 * (int64_t)g6_19;
    int64_t f8g7_19 = f8 * (int64_t)g7_19;
    int64_t f8g8_19 = f8 * (int64_t)g8_19;
    int64_t f8g9_19 = f8 * (int64_t)g9_19;
    int64_t f9g0 = f9 * (int64_t)g0;
    int64_t f9g1_38 = f9_2 * (int64_t)g1_19;
    int64_t f9g2_19 = f9 * (int64_t)g2_19;
    int64_t f9g3_38 = f9_2 * (int64_t)g3_19;
    int64_t f9g4_19 = f9 * (int64_t)g4_19;
    int64_t f9g5_38 = f9_2 * (int64_t)g5_19;
    int64_t f9g6_19 = f9 * (int64_t)g6_19;
    int64_t f9g7_38 = f9_2 * (int64_t)g7_19;
    int64_t f9g8_19 = f9 * (int64_t)g8_19;
    int64_t f9g9_38 = f9_2 * (int64_t)g9_19;
    int64_t h0 = f0g0 + f1g9_38 + f2g8_19 + f3g7_38 + f4g6_19 + f5g5_38 + f6g4_19 + f7g3_38 + f8g2_19 + f9g1_38;
    int64_t h1 = f0g1 + f1g0 + f2g9_19 + f3g8_19 + f4g7_19 + f5g6_19 + f6g5_19 + f7g4_19 + f8g3_19 + f9g2_19;
    int64_t h2 = f0g2 + f1g1_2 + f2g0 + f3g9_38 + f4g8_19 + f5g7_38 + f6g6_19 + f7g5_38 + f8g4_19 + f9g3_38;
    int64_t h3 = f0g3 + f1g2 + f2g1 + f3g0 + f4g9_19 + f5g8_19 + f6g7_19 + f7g6_19 + f8g5_19 + f9g4_19;
    int64_t h4 = f0g4 + f1g3_2 + f2g2 + f3g1_2 + f4g0 + f5g9_38 + f6g8_19 + f7g7_38 + f8g6_19 + f9g5_38;
    int64_t h5 = f0g5 + f1g4 + f2g3 + f3g2 + f4g1 + f5g0 + f6g9_19 + f7g8_19 + f8g7_19 + f9g6_19;
    int64_t h6 = f0g6 + f1g5_2 + f2g4 + f3g3_2 + f4g2 + f5g1_2 + f6g0 + f7g9_38 + f8g8_19 + f9g7_38;
    int64_t h7 = f0g7 + f1g6 + f2g5 + f3g4 + f4g3 + f5g2 + f6g1 + f7g0 + f8g9_19 + f9g8_19;
    int64_t h8 = f0g8 + f1g7_2 + f2g6 + f3g5_2 + f4g4 + f5g3_2 + f6g2 + f7g1_2 + f8g0 + f9g9_38;
    int64_t h9 = f0g9 + f1g8 + f2g7 + f3g6 + f4g5 + f5g4 + f6g3 + f7g2 + f8g1 + f9g0;

    Fe25519 out = Fe25519();
    out.value[0] = h0; out.value[1] = h1; out.value[2] = h2; out.value[3] = h3; out.value[4] = h4;
    out.value[5] = h5; out.value[6] = h6; out.value[7] = h7; out.value[8] = h8; out.value[9] = h9;
    out.carry();
    out.carry();
    out.carry();
    return out;
}
void Fe25519::carry() {
    static const int64_t kTop39Bits = 0xfffffffffe000000LL;
    static const int64_t kTop38Bits = 0xfffffffffc000000LL;
    
    int64_t carry0;
    int64_t carry1;
    int64_t carry2;
    int64_t carry3;
    int64_t carry4;
    int64_t carry5;
    int64_t carry6;
    int64_t carry7;
    int64_t carry8;
    int64_t carry9;

    /* |h0| <= (1.65*1.65*2^52*(1+19+19+19+19)+1.65*1.65*2^50*(38+38+38+38+38))
     *   i.e. |h0| <= 1.4*2^60; narrower ranges forvalue[2,value[4,value[6,value[8
     * |h1| <= (1.65*1.65*2^51*(1+1+19+19+19+19+19+19+19+19))
     *   i.e. |h1| <= 1.7*2^59; narrower ranges forvalue[3,value[5,value[7,value[9 */

    carry0 =value[0] + (1 << 25);
   value[1] += carry0 >> 26;
   value[0] -= carry0 & kTop38Bits;
    carry4 =value[4] + (1 << 25);
   value[5] += carry4 >> 26;
   value[4] -= carry4 & kTop38Bits;
    /* |h0| <= 2^25 */
    /* |h4| <= 2^25 */
    /* |h1| <= 1.71*2^59 */
    /* |h5| <= 1.71*2^59 */

    carry1 =value[1] + (1 << 24);
   value[2] += carry1 >> 25;
   value[1] -= carry1 & kTop39Bits;
    carry5 =value[5] + (1 << 24);
   value[6] += carry5 >> 25;
   value[5] -= carry5 & kTop39Bits;
    /* |h1| <= 2^24; from now on fits into int32 */
    /* |h5| <= 2^24; from now on fits into int32 */
    /* |h2| <= 1.41*2^60 */
    /* |h6| <= 1.41*2^60 */

    carry2 =value[2] + (1 << 25);
   value[3] += carry2 >> 26;
   value[2] -= carry2 & kTop38Bits;
    carry6 =value[6] + (1 << 25);
   value[7] += carry6 >> 26;
   value[6] -= carry6 & kTop38Bits;
    /* |h2| <= 2^25; from now on fits into int32 unchanged */
    /* |h6| <= 2^25; from now on fits into int32 unchanged */
    /* |h3| <= 1.71*2^59 */
    /* |h7| <= 1.71*2^59 */

    carry3 =value[3] + (1 << 24);
   value[4] += carry3 >> 25;
   value[3] -= carry3 & kTop39Bits;
    carry7 =value[7] + (1 << 24);
   value[8] += carry7 >> 25;
   value[7] -= carry7 & kTop39Bits;
    /* |h3| <= 2^24; from now on fits into int32 unchanged */
    /* |h7| <= 2^24; from now on fits into int32 unchanged */
    /* |h4| <= 1.72*2^34 */
    /* |h8| <= 1.41*2^60 */

    carry4 =value[4] + (1 << 25);
   value[5]+= carry4 >> 26;
   value[4] -= carry4 & kTop38Bits;
    carry8 =value[8] + (1 << 25);
   value[9] += carry8 >> 26;
   value[8] -= carry8 & kTop38Bits;
    /* |h4| <= 2^25; from now on fits into int32 unchanged */
    /* |h8| <= 2^25; from now on fits into int32 unchanged */
    /* |h5| <= 1.01*2^24 */
    /* |h9| <= 1.71*2^59 */

    carry9 =value[9] + (1 << 24);
   value[0] += (carry9 >> 25) * 19;
   value[9] -= carry9 & kTop39Bits;
    /* |h9| <= 2^24; from now on fits into int32 unchanged */
    /* |h0| <= 1.1*2^39 */

    carry0 =value[0] + (1 << 25);
   value[1] += carry0 >> 26;
   value[0] -= carry0 & kTop38Bits;
    /* |h0| <= 2^25; from now on fits into int32 unchanged */
    /* |h1| <= 1.01*2^24 */
}


Fe25519::operator std::string() const {
    Fe25519 temp = *this;
    temp.carry();

    uint8_t bytes[32];
    const int64_t* v = temp.value;

    // 2. Побитовая сборка (упаковка Radix 25.5 -> 8-bit bytes)
    // Каждые 8 байт (64 бита) собираются из кусков лимб
    bytes[0] = (uint8_t)(v[0]);
    bytes[1] = (uint8_t)(v[0] >> 8);
    bytes[2] = (uint8_t)(v[0] >> 16);
    bytes[3] = (uint8_t)((v[0] >> 24) | (v[1] << 2));
    bytes[4] = (uint8_t)(v[1] >> 6);
    bytes[5] = (uint8_t)(v[1] >> 14);
    bytes[6] = (uint8_t)((v[1] >> 22) | (v[2] << 3));
    bytes[7] = (uint8_t)(v[2] >> 5);
    bytes[8] = (uint8_t)(v[2] >> 13);
    bytes[9] = (uint8_t)((v[2] >> 21) | (v[3] << 5));
    bytes[10] = (uint8_t)(v[3] >> 3);
    bytes[11] = (uint8_t)(v[3] >> 11);
    bytes[12] = (uint8_t)((v[3] >> 19) | (v[4] << 6));
    bytes[13] = (uint8_t)(v[4] >> 2);
    bytes[14] = (uint8_t)(v[4] >> 10);
    bytes[15] = (uint8_t)(v[4] >> 18);
    bytes[16] = (uint8_t)((v[4] >> 26) | (v[5] << 0));
    bytes[17] = (uint8_t)(v[5] >> 8);
    bytes[18] = (uint8_t)(v[5] >> 16);
    bytes[19] = (uint8_t)((v[5] >> 24) | (v[6] << 1));
    bytes[20] = (uint8_t)(v[6] >> 7);
    bytes[21] = (uint8_t)(v[6] >> 15);
    bytes[22] = (uint8_t)((v[6] >> 23) | (v[7] << 3));
    bytes[23] = (uint8_t)(v[7] >> 5);
    bytes[24] = (uint8_t)(v[7] >> 13);
    bytes[25] = (uint8_t)((v[7] >> 21) | (v[8] << 4));
    bytes[26] = (uint8_t)(v[8] >> 4);
    bytes[27] = (uint8_t)(v[8] >> 12);
    bytes[28] = (uint8_t)((v[8] >> 20) | (v[9] << 6));
    bytes[29] = (uint8_t)(v[9] >> 2);
    bytes[30] = (uint8_t)(v[9] >> 10);
    bytes[31] = (uint8_t)(v[9] >> 18);

    // 3. Форматирование в HEX-строку
    std::string result;
    for (int i = 0; i < 32; i++) {
        char buf[3];
        snprintf(buf, sizeof(buf), "%02X", bytes[i]);
        result += buf;
        result += ":";
    }
    return result;
}
Fe25519 Fe25519::One() {
    Fe25519 result;
    for (int i = 0; i < 10; ++i) result.value[i] = 0;
    result.value[0] = 1;
    return result;
}
Fe25519 Fe25519::Zero() {
    Fe25519 result;
    for (int i = 0; i < 10; ++i) result.value[i] = 0;
    return result;
}
