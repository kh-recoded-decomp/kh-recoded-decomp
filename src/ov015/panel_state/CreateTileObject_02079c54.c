#include "nitro/types.h"

extern void *func_0202a178();
extern void func_020014b0();
extern void func_ov015_02079bc0();
extern void func_0200153c();
extern u32 func_0202b3b8();
extern void func_02001a60();

/* Allocates and registers a tiled graphics object. */
void *CreateTileObject_02079c54(u32 ownerId, u32 value, u16 *layout, void *tileData, void *mapData) {
    void *context;
    u32 id;

    context = func_0202a178(0x34);
    func_020014b0(context, ownerId, 0, value, layout);
    func_ov015_02079bc0(context, layout, tileData, mapData);
    func_0200153c(context);
    id = func_0202b3b8(ownerId);
    func_02001a60(context, id, layout[0], layout[1], layout[5] & 0xff);
    return context;
}
