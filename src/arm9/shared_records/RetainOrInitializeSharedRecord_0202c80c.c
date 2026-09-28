/* Increments an occupied record count or initializes its metadata and payload at offset 0x14.
 * The direct store and payload helper pointer both use 0x14. The upstream SND_RegisterSeq alias does not establish sound semantics.
 * Adapted CC0 C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_RegisterSeq.c. */
extern void *func_0202c6cc(int a, int b);
extern int func_0202c478(int a, int b);
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
} Slot_0201f510;

void *RetainOrInitializeSharedRecord_0202c80c(int a, int b) {
    Slot_0201f510 *p = (Slot_0201f510 *)func_0202c6cc(a, b);
    int v;

    if (p->s0 != 0) {
        p->s0++;
        data_02060564[0x14 / 4] = 0;
        return p;
    }

    v = data_02060564[0x14 / 4];
    if (v == 0) {
        v = func_0202a158();
    }
    p->w8 = v;
    p->wc = func_0202c478(a, b);
    if (a & 0x80000000) {
        p->payload14 = a;
    } else {
        func_02021e60(&p->payload14, a);
    }
    p->s0 = 1;
    p->s2 = 0;
    p->s4 = 0;
    p->s6 = (unsigned short)b;
    return p;
}
