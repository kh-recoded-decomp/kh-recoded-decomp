extern int GFXi_EnqueueCommand(void *a, int b, int c, int d);
extern void *data_02055744[];

int Gfx_EnqueueTableCmdAtC_0202b460(int idx, void *p, int arg2, int arg3) {
    return GFXi_EnqueueCommand(data_02055744[idx], arg2, (int)((char *)p + 0xc), arg3);
}
