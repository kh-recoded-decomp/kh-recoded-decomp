/* Writes a value into an MSB-first packed bit array, splitting fields across 32-bit words with a logical right shift.
 * The single changed ARM instruction is LSR rather than ASR; the source value is unsigned.
 * Adapted CC0 C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, src/auto/func_02025754.c. */

typedef unsigned int u32;
void WritePackedBits_0202d560(u32 *base, u32 bitOffset, u32 bitCount, u32 value)
{
    u32 mask;
    u32 n;
    base += (int)bitOffset / 32;
    bitOffset &= 0x1f;
    if ((int)(bitOffset + bitCount) > 0x20) {
        do {
            n = 0x20 - bitOffset;
            mask = (n == 0x20) ? 0xffffffff : (1u << n) - 1;
            bitCount -= n;
            *base = (*base & ~mask) | (mask & (value >> bitCount));
            base++;
            bitOffset = 0;
        } while ((int)bitCount > 0x20);
    }
    if ((int)bitCount > 0) {
        mask = (bitCount == 0x20) ? 0xffffffff : (1u << bitCount) - 1;
        n = (0x20 - bitOffset) - bitCount;
        *base = (*base & ~(mask << n)) | ((value & mask) << n);
    }
}
