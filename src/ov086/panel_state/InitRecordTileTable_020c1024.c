#include "nitro/types.h"

typedef struct {
    u32 first;
    u32 second;
} TileRange;

typedef struct {
    TileRange *range;
    u32 width;
    u32 height;
    u32 flags;
} TileTableDesc;

extern const TileRange data_ov086_020c20d4;
extern const TileTableDesc data_ov086_020c20f8;
extern void InitTileTableFrom_020b9a0c(void *table, const TileTableDesc *source);

void InitRecordTileTable_020c1024(u8 *menu)
{
    TileRange range = data_ov086_020c20d4;
    TileTableDesc desc = data_ov086_020c20f8;

    desc.range = &range;
    InitTileTableFrom_020b9a0c(menu + 0x174, &desc);
}
