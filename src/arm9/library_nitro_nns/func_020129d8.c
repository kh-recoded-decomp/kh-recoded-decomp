/* Unlinks an object from an offset-based doubly linked list and clears embedded links.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/auto/NNS_FndRemoveListObject.c.
 * Original routine: NNS_FndRemoveListObject. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned short u16;

struct NNSFndLink {
    void *prev_object;
    void *next_object;
};

struct NNSFndList {
    void *head_object;
    void *tail_object;
    u16 num_objects;
    u16 offset;
};

void RemoveIntrusiveListObject_020129d8(struct NNSFndList *list, void *object)
{
    struct NNSFndLink *link =
        (struct NNSFndLink *)((char *)object + list->offset);
    if (link->prev_object == 0) {
        list->head_object = link->next_object;
    } else {
        ((struct NNSFndLink *)((char *)link->prev_object + list->offset))->next_object =
            link->next_object;
    }
    if (link->next_object == 0) {
        list->tail_object = link->prev_object;
    } else {
        ((struct NNSFndLink *)((char *)link->next_object + list->offset))->prev_object =
            link->prev_object;
    }
    link->prev_object = 0;
    link->next_object = 0;
    list->num_objects--;
}
