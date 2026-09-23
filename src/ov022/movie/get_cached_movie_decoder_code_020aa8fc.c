/* Returns a cached decoder code pointer, copying the embedded code into a fast-memory arena when capacity permits.
 * Evidence: Cache slots, size `0x659c`, copy call, and fallback path in source.
 * Uncertainty: Fast-memory arena layout is opaque outside the movie module.
 * Source: src/overlays/ov024/calls/func_ov024_02086620.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */

extern void MIi_CpuCopyFast(const void *src, void *dest, unsigned int size);
extern int data_020b7df4[];
extern unsigned char data_020b0ba0[];

void *get_cached_movie_decoder_code_020aa8fc(void) {
    void *decoderCode;

    if (data_020b7df4[2] == 0) {
        if ((unsigned int)data_020b7df4[5] >= 0x659c) {
            decoderCode = (void *)data_020b7df4[6];
            data_020b7df4[2] = (int)decoderCode;
            MIi_CpuCopyFast(data_020b0ba0, decoderCode, 0x659c);
            data_020b7df4[6] += 0x659c;
            data_020b7df4[5] -= 0x659c;
        } else {
            return data_020b0ba0;
        }
    }
    return (void *)data_020b7df4[2];
}
