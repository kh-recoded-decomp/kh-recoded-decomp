#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    void *buffer;
} LayerSet;

typedef struct {
    u8 count;
    u8 pad_01[3];
    void *extraData;
    LayerSet *sets[1];
} LayerSetTable;

typedef struct {
    LayerSetTable *table;
    u32 unk04;
    void *resource;
    s8 prevSetIndex;
    s8 setIndex;
    u8 pad_0e[0x10bc - 0xe];
    void *workBuffer;
} LayerContext;

extern LayerContext *data_ov001_020a046c;
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void ZeroHalfThenFree_0202cd78(void *resource);

void FreeLayerContextData_02067aa8(void)
{
    LayerContext *ctx = data_ov001_020a046c;
    LayerSetTable *table = ctx->table;
    int i;

    if (table != NULL) {
        for (i = 0; i < table->count; i++) {
            if (table->sets[i]->buffer != NULL) {
                NNSi_FndFreeFromDefaultHeap_0202a1c4(table->sets[i]->buffer);
            }
            table = ctx->table;
        }
        if (table->extraData != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(table->extraData);
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(ctx->table);
        ctx->table = NULL;
    }
    if (ctx->workBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(ctx->workBuffer);
        ctx->workBuffer = NULL;
    }
    if (ctx->resource != NULL) {
        ZeroHalfThenFree_0202cd78(ctx->resource);
        ctx->resource = NULL;
    }
    ctx->prevSetIndex = -1;
    ctx->setIndex = -1;
}
