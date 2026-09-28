/* Inserts a free block into a doubly linked list and repairs head/tail links.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/auto/InsertMBlock.c.
 * Original routine: InsertMBlock. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef struct InsertMBlock_node {
    char pad[8];
    struct InsertMBlock_node *prev;
    struct InsertMBlock_node *next;
} InsertMBlock_node;

typedef struct {
    InsertMBlock_node *head;
    InsertMBlock_node *tail;
} InsertMBlock_list;

InsertMBlock_node *InsertFreeMemoryBlock_02012c24(InsertMBlock_list *list, InsertMBlock_node *node, InsertMBlock_node *prev)
{
    InsertMBlock_node *next;

    node->prev = prev;
    if (prev != 0) {
        next = prev->next;
        prev->next = node;
    } else {
        next = list->head;
        list->head = node;
    }
    node->next = next;
    if (next != 0) {
        next->prev = node;
    } else {
        list->tail = node;
    }
    return node;
}
