extern void *G2S_GetBG3ScrPtr(void);
void *GetSubScreenBuffer_020a7d7c(int direct) {
    if (direct != 0) {
        return (void *)0x6600000;
    }
    return G2S_GetBG3ScrPtr();
}
