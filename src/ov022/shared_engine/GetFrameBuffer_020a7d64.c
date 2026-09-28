extern void *G2_GetBG3ScrPtr(void);
void *GetFrameBuffer_020a7d64(int direct) {
    if (direct != 0) {
        return (void *)0x6400000;
    }
    return G2_GetBG3ScrPtr();
}
