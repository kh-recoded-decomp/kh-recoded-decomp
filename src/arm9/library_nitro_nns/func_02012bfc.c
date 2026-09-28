/* Unlinks a block from a doubly linked free list and returns its former predecessor.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/auto/RemoveMBlock.c.
 * Original routine: RemoveMBlock. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef struct Link020102ec {
    int pad0;
    int pad4;
    struct Link020102ec *prev;
    struct Link020102ec *next;
} Link020102ec;

Link020102ec *RemoveFreeMemoryBlock_02012bfc(Link020102ec **list, Link020102ec *node)
{
    Link020102ec *prev = node->prev;
    Link020102ec *next = node->next;

    if (prev != 0) {
        prev->next = next;
    } else {
        list[0] = next;
    }

    if (next != 0) {
        next->prev = prev;
    } else {
        list[1] = prev;
    }

    return prev;
}
