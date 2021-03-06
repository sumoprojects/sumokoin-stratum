#include "crypto/hash-ops.h"

void cryptonight_hash(const char* input, char* output, uint32_t len, uint64_t height) {
    const int variant = input[0] >= 7 ? input[0] - 6 : 0;
    cn_monero_slow_hash(input, len, output, variant, 0, height);
}

void cryptonight_fast_hash(const char* input, char* output, uint32_t len) {
    cn_fast_hash(input, len, output);
}
