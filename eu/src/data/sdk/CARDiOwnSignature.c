#include "libs/nitro/os/os_types_internal.h"

typedef struct CARDiOwnSignatureStorage {
    u8 moduleSignature[0x88];
    u8 alignmentPadding[0x0c];
} CARDiOwnSignatureStorage;

typedef char CardSignatureStorageMustBe148Bytes[
    sizeof(CARDiOwnSignatureStorage) == 148 ? 1 : -1];

/* CARDi_InitRom reads 136 signature bytes. The trailing 12 bytes keep the
 * following ROM cache at its original 32-byte alignment. */
CARDiOwnSignatureStorage CARDiOwnSignature;
