extern void Obj_Release(void *context);
extern void Ov008_DestroyAllListObjects(void *context);

typedef struct {
    char pad[25720];
    unsigned int flags;
} Unk02054364;

void DestroyObjectsAndRelease_020b8c58(Unk02054364 *context)
{
    Ov008_DestroyAllListObjects(context);

    if (((context->flags << 29) >> 31) == 1) {
        Obj_Release(context);
        context->flags &= ~4;
    }
}
