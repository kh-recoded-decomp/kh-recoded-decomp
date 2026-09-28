#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *field_08;
    u8 pad_0c[0x820 - 0xc];
    void *field_820;
} ActorRegistry;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void FreeRecordArrayAndReset_02035178(void *table);
extern ActorRegistry *g_actorRegistry_0206083c;

BOOL func_02035774(void) {
    ActorRegistry *table = g_actorRegistry_0206083c;
    if (table != NULL) {
        if (table->field_820 != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(table->field_820);
            table->field_820 = NULL;
        }
        FreeRecordArrayAndReset_02035178(table);
        if (table->field_08 != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(table->field_08);
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(table);
        g_actorRegistry_0206083c = NULL;
    }
    return TRUE;
}
