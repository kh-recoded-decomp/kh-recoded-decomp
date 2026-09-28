#include "nitro/types.h"

extern void func_0200d9b0(void *digest, const void *data, u32 len);
extern int compareByteStrings_02021c54(const void *a, const void *b, u32 len);

typedef struct SignedBlob {
    s32 magic;
    u8 hash[0x14];
    u8 data[0x3760];
} SignedBlob;

BOOL VerifySha1Signature_02026c9c(SignedBlob *blob) {
    u8 digest[0x14];

    if (blob->magic != -0x3c086c5d) {
        return 0;
    }
    func_0200d9b0(digest, blob->data, 0x3760);
    if (compareByteStrings_02021c54(digest, blob->hash, 0x14) == 0) {
        return 1;
    }
    return 0;
}
