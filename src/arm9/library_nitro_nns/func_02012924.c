/* Prepends an object to an offset-based doubly linked list.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/NNS_FndPrependListObject.c.
 * Original routine: NNS_FndPrependListObject. External references are
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

extern void SetFirstObject(struct NNSFndList *list, void *object);

void PrependIntrusiveListObject_02012924(struct NNSFndList *list, void *object)
{
    if (list->head_object == 0) {
        SetFirstObject(list, object);
    } else {
        struct NNSFndLink *link =
            (struct NNSFndLink *)((char *)object + list->offset);
        link->prev_object = 0;
        link->next_object = list->head_object;
        ((struct NNSFndLink *)((char *)list->head_object + list->offset))->prev_object = object;
        list->head_object = object;
        list->num_objects++;
    }
}
