/* Walks variable-stride records, maps each kind to a priority, creates a sprite, and places it at the record coordinates.
 * Evidence: Record count/stride, kind lookup, sprite constructor, and placement helper in source.
 * Uncertainty: Exact record type and sprite semantic role remain unknown.
 * Source: src/overlays/ov000/calls/func_ov000_02055ee4.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */

extern int func_020b7e5c(int spriteContext, int recordField06, int recordField04, int recordField0c,
                               int recordField0e, int recordField10, int recordField12, int priority);
extern void func_020b81e8(int self, int spriteHandle, int x, int y);
extern unsigned char data_020ba368;
extern unsigned char data_020ba364;
void build_and_place_record_sprites_020b77c0(int spriteContext, int records) {
    unsigned int recordCount = *(unsigned int *)records;
    int recordCursor = records + 4;
    unsigned int recordIndex;
    for (recordIndex = 0; recordIndex < recordCount; recordIndex++) {
        unsigned int spriteKind = *(unsigned short *)(recordCursor + 0x14);
        unsigned char priority = spriteKind >= 0xa ? (&data_020ba368)[spriteKind - 0xa]
                                          : (&data_020ba364)[spriteKind];
        int spriteHandle = func_020b7e5c(spriteContext, *(unsigned short *)(recordCursor + 6),
            *(unsigned short *)(recordCursor + 4), *(unsigned short *)(recordCursor + 0xc),
            *(unsigned short *)(recordCursor + 0xe), *(short *)(recordCursor + 0x10),
            *(short *)(recordCursor + 0x12), priority);
        func_020b81e8(spriteContext, spriteHandle, *(short *)(recordCursor + 8), *(short *)(recordCursor + 0xa));
        recordCursor += *(int *)recordCursor;
    }
}
