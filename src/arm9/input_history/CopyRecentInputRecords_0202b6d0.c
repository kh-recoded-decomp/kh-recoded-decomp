/* When shared status bit 15 is clear, copies four converted eight-byte records from a five-entry circular history.
 * The BK9E status address is 0x02ffffa8; body uses an index provider and four wrap-adjusted copies. Upstream GX alias is not trusted.
 * Adapted CC0 C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, src/calls/func_02024da4.c. */
typedef unsigned short u16;


typedef struct {
    u16 field_00;
    u16 field_02;
    u16 field_04;
    u16 field_06;
} Rec;

extern int func_0200ff50(void);
extern void func_020100e0(Rec *out, Rec *in);
extern void func_01ff89a8(const void *src, void *dst, unsigned int len);
extern Rec data_02060534[];

int CopyRecentInputRecords_0202b6d0(Rec *table) {
    int bank;
    int i;
    short count = 0;

    if (!((*(volatile u16 *)0x02ffffa8 & 0x8000) >> 15)) {
        Rec buf;

        bank = func_0200ff50();
        i = 0;
        bank -= 3;

        for (; i < 4; i++) {
            int idx = bank + i;
            if (idx < 0) {
                idx += 5;
            }
            func_020100e0(&buf, &data_02060534[idx]);
            func_01ff89a8(&buf, &table[count++], 8);
        }
    }

    return count;
}
