/* Unlinks a node from a doubly linked chain and returns updated tail when needed.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/auto/DLExtract.c.
 * Original routine: DLExtract. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef struct Unk02002c0c {
    struct Unk02002c0c *next;
    struct Unk02002c0c *prev;
} Unk02002c0c;

Unk02002c0c *ExtractDoubleLinkedNode_020038d8(Unk02002c0c *tail, Unk02002c0c *node)
{
    if (node->prev != 0) {
        node->prev->next = node->next;
    }

    if (node->next == 0) {
        tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }

    return tail;
}
