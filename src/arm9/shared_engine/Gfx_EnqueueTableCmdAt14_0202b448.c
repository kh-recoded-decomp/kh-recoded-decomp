extern int GFXi_EnqueueCommand(void *a, int b, int c, int d);
extern void *data_02055724[];

int Gfx_EnqueueTableCmdAt14_0202b448(int idx, void *p, int arg2, int arg3) {
    return GFXi_EnqueueCommand(data_02055724[idx], arg2, *(int *)((char *)p + 0x14), arg3);
}
