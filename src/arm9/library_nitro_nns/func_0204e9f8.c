/* Appends a node to a null-terminated doubly linked chain.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/NNS_FndAppendDoubleListObject.c.
 * Original routine: NNS_FndAppendDoubleListObject. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
struct Node {
    struct Node *prev;
    struct Node *next;
};

void AppendDoubleLinkedNode_0204e9f8(struct Node **head, struct Node *node)
{
    struct Node *tail = *head;
    if (tail == 0) {
        node->prev = 0;
        *head = node;
    } else {
        while (tail->next != 0) {
            tail = tail->next;
        }
        node->prev = tail;
        tail->next = node;
    }
    node->next = 0;
}
