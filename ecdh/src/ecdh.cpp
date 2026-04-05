#include "ecdh.h"
#include "uint256.h"
#include "Fe25519.h"
#include <iostream>
using namespace std;
static void printKey(const char* label, const UInt256& k) {
    printf("%s: ", label);
    for (int i = 0; i < 32; i++) printf("%02x", k.key[i]);
    printf("\n");
}

UInt256 ScalarMult(UInt256& scalar, const UInt256& point) {
    Fe25519 x1, x2, z2, x3, z3, tmp0, tmp1;
    uint8_t e[32];
    unsigned swap = 0;
    int pos;
    memcpy(e, scalar.key, 32);

    x1 = Fe25519(point);
    x2 = Fe25519::One();
    z2 = Fe25519::Zero();
    x3 = x1;
    z3 = Fe25519::One();


    for (pos = 254; pos >= 0; --pos) {
        unsigned b = 1 & (e[pos / 8] >> (pos & 7));
        
        swap ^= b;
        cswap(x2, x3, swap);
        cswap(z2, z3, swap);
        swap = b;
        
        Fe25519 A = x2 + z2;
        Fe25519 B = x2 - z2;
        Fe25519 C = x3 + z3;
        Fe25519 D = x3 - z3;

        Fe25519 AA = A.square();
        Fe25519 BB = B.square();
        Fe25519 E = AA - BB;

        Fe25519 DA = D * A;
        Fe25519 CB = C * B;

        // Обновление R1 (сложение)
        x3 = (DA + CB).square();
        z3 = (DA - CB).square() * x1;

        // Обновление R0 (удвоение)
        x2 = AA * BB;
        z2 = E * (BB + E.mul_a24());
    }
    cswap(x2, x3, swap);
    cswap(z2, z3, swap);

    z2 = z2.inverse();
    x2 = x2 * z2;
    
    return UInt256(x2);
}
void cswap(Fe25519& R0, Fe25519& R1, unsigned int bit) {
    /*
    если b = 0
    b    = 0000 0000
    ~b   = 1111 1111
    ~b+1 = 0000 0000  ← переполнение, все биты = 0
    -b   = 0x00

    если b = 1
    b    = 0000 0001
    ~b   = 1111 1110
    ~b+1 = 1111 1111  ← все биты = 1
    -b   = 0xFF
    */
    int64_t mask = -(int64_t)(bit & 1);
    for (int i = 0; i < 10; i++) {
        int64_t x = R0.value[i] ^ R1.value[i];
        x &= mask;
        R0.value[i] ^= x;
        R1.value[i] ^= x;
    }

}