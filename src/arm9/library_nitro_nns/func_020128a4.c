/* Makes an object sole head/tail and clears its embedded links.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/auto/SetFirstObject.c.
 * Original routine: SetFirstObject. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef struct List0200ff94 {
    void *head;
    void *tail;
    unsigned short count;
    unsigned short offset;
} List0200ff94;

void SetFirstIntrusiveListObject_020128a4(List0200ff94 *list, void *node)
{
    char *link = (char *)node + list->offset;

    *(void **)(link + 4) = 0;
    *(void **)link = 0;
    list->head = node;
    list->tail = node;
    list->count++;
}
