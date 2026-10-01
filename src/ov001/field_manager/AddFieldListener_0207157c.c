#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x5d0];
    u8 listeners[0xc];
} FieldManager;

typedef struct FieldManagerHandle {
    BOOL ready;
    FieldManager *manager;
} FieldManagerHandle;

typedef struct FieldListener {
    int value;
    u8 link[0xc];
} FieldListener;

extern FieldManagerHandle data_ov001_020a04a4;
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void AppendIntrusiveListObject_020128d0(void *list, void *object);

FieldListener *AddFieldListener_0207157c(int value)
{
    FieldListener *listener;

    data_ov001_020a04a4.ready = FALSE;
    listener = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(FieldListener));
    listener->value = value;
    AppendIntrusiveListObject_020128d0(data_ov001_020a04a4.manager->listeners, listener);
    data_ov001_020a04a4.ready = TRUE;
    return listener;
}
