/* Initializes a frame heap with FRMH signature and resets allocation cursors/count.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/NNSi_FndInitExpHeap.c.
 * Original routine: NNSi_FndInitExpHeap. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
extern void NNSi_FndInitHeapHead(void *hh, unsigned magic, void *start, void *end, int opt);

void *InitializeFrameHeap_02013388(void *hh_void, void *end, int opt) {
    char *hh = (char*)hh_void;
    NNSi_FndInitHeapHead(hh, 0x46524D48, hh + 0x30, end, opt);
    *(int*)(hh + 0x24) = *(int*)(hh + 0x18);
    *(int*)(hh + 0x28) = *(int*)(hh + 0x1c);
    *(int*)(hh + 0x2c) = 0;
    return hh;
}
