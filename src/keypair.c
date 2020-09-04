#include "secp256k1.h"
#include "sha3.h"
#include "uECC.h"
#include "types.h"

#include <string.h>

void secp256k1_compress_pubkey(unsigned char *compressed, const unsigned char *public_key) {
    if (public_key[0] == 0x04) {
        uECC_compress(public_key + 1, compressed);
    } else {
        memcpy(compressed, public_key, 33);
    }
}

void secp256k1_decompress_pubkey(unsigned char *decompressed, const unsigned char *public_key) {
    if (public_key[0] != 0x04) {
        decompressed[0] = 0x04;
        uECC_decompress(public_key, decompressed + 1);
    } else {
        memcpy(decompressed, public_key, 65);
    }
}

void secp256k1_get_compressed_pubkey(unsigned char *public_key, const unsigned char *private_key) {
    unsigned char tmp[64];
    uECC_compute_public_key(private_key, tmp);
    uECC_compress(tmp, public_key);
}

void secp256k1_get_uncompressed_pubkey(unsigned char *public_key, const unsigned char *private_key) {
    public_key[0] = 0x04;
    uECC_compute_public_key(private_key, public_key);
}

void secp256k1_get_pubkey(unsigned char *public_key, const unsigned char *private_key) {
    return secp256k1_get_compressed_pubkey(public_key, private_key);
}

void secp256k1_create_privkey(unsigned char *private_key, const unsigned char *seed) {
    sha3_256(seed, 32, private_key);
}

void secp256k1_create_keypair(unsigned char *public_key, unsigned char *private_key, const unsigned char *seed) {
    sha3_256(seed, 32, private_key);
    secp256k1_get_pubkey(public_key, private_key);
}
