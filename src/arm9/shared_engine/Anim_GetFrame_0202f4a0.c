extern int *Anim_GetChannelState();

int Anim_GetFrame_0202f4a0(unsigned short *r0, int r1) {
    int *p = Anim_GetChannelState(r0, r1);
    if (p == 0) return 0;
    return *p;
}
