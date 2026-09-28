/* Reuses an occupied record by incrementing its count or initializes a record and stores its payload at offset 0x14.
 * Two target address calculations use payload offset 0x14 rather than the Days offset 0x10; the related acquire routine has the same layout.
 * Adapted CC0 C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, src/calls/func_0201f468.c. */
extern void *func_0202c6cc(int a, int b);
extern int func_0202c364(int a, int b);
extern void func_02021e60(void *dst, int src);
extern int func_0202a158(void);

extern int data_02060564[];

typedef struct {
    unsigned short s0;
    unsigned short s2;
    unsigned short s4;
    unsigned short s6;
    int w8;
    int wc;
    int reserved10;
    int payload14;
} Slot_0201f468;

int AcquireSharedRecord_0202c764(int a, Slot_0201f468 **out, int c) {
    Slot_0201f468 *p = (Slot_0201f468 *)func_0202c6cc(a, (int)out);
    int v;

    if (p->s0 != 0) {
        p->s0++;
        *out = p;
        data_02060564[0x14 / 4] = 0;
        return 1;
    }

    v = data_02060564[0x14 / 4];
    if (v == 0) {
        v = func_0202a158();
    }
    p->w8 = v;
    p->wc = func_0202c364(a, c);
    if (a & 0x80000000) {
        p->payload14 = a;
    } else {
        func_02021e60(&p->payload14, a);
    }
    p->s0 = 1;
    p->s2 = 0;
    p->s4 = 0;
    p->s6 = (unsigned short)c;
    *out = p;
    return 0;
}
