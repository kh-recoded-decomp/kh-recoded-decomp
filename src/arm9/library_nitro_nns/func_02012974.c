/* Inserts before a requested object; null means append and head means prepend.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/NNS_FndInsertListObject.c.
 * Original routine: NNS_FndInsertListObject. External references are
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

extern void NNS_FndAppendListObject(struct NNSFndList *list, void *object);
extern void NNS_FndPrependListObject(struct NNSFndList *list, void *object);

void InsertIntrusiveListObject_02012974(struct NNSFndList *list, void *where, void *object)
{
    if (where == 0) {
        NNS_FndAppendListObject(list, object);
    } else if (where == list->head_object) {
        NNS_FndPrependListObject(list, object);
    } else {
        struct NNSFndLink *link =
            (struct NNSFndLink *)((char *)object + list->offset);
        void *previousObject =
            ((struct NNSFndLink *)((char *)where + list->offset))->prev_object;
        struct NNSFndLink *previousLink =
            (struct NNSFndLink *)((char *)previousObject + list->offset);
        link->prev_object = previousObject;
        link->next_object = where;
        previousLink->next_object = object;
        ((struct NNSFndLink *)((char *)where + list->offset))->prev_object = object;
        list->num_objects++;
    }
}
