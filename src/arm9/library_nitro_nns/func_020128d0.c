/* Appends an object to an offset-based list, initializing an empty list when needed.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/NNS_FndAppendListObject.c.
 * Original routine: NNS_FndAppendListObject. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Appends an object to the tail of an intrusive list, or seeds an empty one. */
extern void SetFirstObject(void *list, void *obj);

void AppendIntrusiveListObject_020128d0(char *list, char *obj) {
    unsigned short off;
    char *tail;
    if (*(void **)list == 0) {
        SetFirstObject(list, obj);
        return;
    }
    off = *(unsigned short *)(list + 0xa);
    *(void **)(obj + off) = *(void **)(list + 4);
    *(void **)(obj + off + 4) = 0;
    tail = *(char **)(list + 4) + *(unsigned short *)(list + 0xa);
    *(void **)(tail + 4) = obj;
    *(void **)(list + 4) = obj;
    *(unsigned short *)(list + 8) = (unsigned short)(*(unsigned short *)(list + 8) + 1);
}
