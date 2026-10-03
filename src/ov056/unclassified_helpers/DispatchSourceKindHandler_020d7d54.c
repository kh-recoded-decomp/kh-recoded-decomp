#include "nitro/types.h"

typedef struct EffectSource {
    u8 pad_00[0x3d];
    s8 kind;
} EffectSource;

typedef void (*SourceHandler)(EffectSource *source);

typedef struct SourceHandlerTable {
    SourceHandler handlers[20];
} SourceHandlerTable;

extern const SourceHandlerTable data_ov056_020d7fc0;

void DispatchSourceKindHandler_020d7d54(EffectSource *source)
{
    SourceHandlerTable table = data_ov056_020d7fc0;
    if (table.handlers[source->kind] != NULL) {
        table.handlers[source->kind](source);
    }
}
