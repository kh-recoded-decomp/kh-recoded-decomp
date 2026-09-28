#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void MI_CpuFill32_01ff8740(u32 value, void *dest, u32 size);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern int WriteCardBackupSync_02026b28(u32 backupOffset, void *buffer, u32 length);
extern const void *g_backupSignature_02055f30;

BOOL FormatCardBackup_02026d30(void)
{
    int block;
    int offset;
    BOOL success = TRUE;
    u8 *header = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x20, 0x20);
    int slot;
    int copy;

    MI_CpuFill32_01ff8740(0, header, 0x20);
    for (slot = 0; slot < 2; slot++) {
        for (block = 0; block < 2; block++) {
            if (WriteCardBackupSync_02026b28((block + slot * 2) * 0x3c18 + 0x20, header, 0x20) != 0) {
                success = FALSE;
                goto done;
            }
        }
    }
    for (offset = 0, copy = 0; copy < 4; copy++, offset += 8) {
        MI_CpuCopy8_01ff89a8(g_backupSignature_02055f30, header + offset, 8);
    }
    if (WriteCardBackupSync_02026b28(0, header, 0x20) != 0) {
        success = FALSE;
    }
done:
    NNSi_FndFreeFromDefaultHeap_0202a1c4(header);
    return success;
}
