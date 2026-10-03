#include "nitro/types.h"

extern void *func_ov001_0207b748(void);
extern int func_ov001_0207b73c(void);
extern u16 *func_ov027_020ba2e0(void *messages, int index, u16 *buffer, int size, ...);
extern void CallVirtualHandlerSlot1_02001574(void *object, int arg);
extern u32 GetFieldFont2_020711d4(void);
extern void func_0200160c(void *context, u32 x, u32 y, u32 color, u32 flags, u16 *text, u32 font, int maxWidth);
extern void Text_UploadTileBuffer_02001520(void *context);

void DrawRemainingCountText_020b5858(u8 *screen, int count)
{
    u16 buffer[64];

    if (*(int *)(screen + 0x66d8) != 0) {
        if (count >= 4) {
            func_ov027_020ba2e0(func_ov001_0207b748(), 1, buffer, 0x40, func_ov001_0207b73c());
        } else {
            func_ov027_020ba2e0(func_ov001_0207b748(), 0, buffer, 0x40, func_ov001_0207b73c(), count);
        }
        CallVirtualHandlerSlot1_02001574(screen + 0x6634, 0);
        func_0200160c(screen + 0x6634, 4, 3, 2, 0x209, buffer, GetFieldFont2_020711d4(), 0x84);
        Text_UploadTileBuffer_02001520(screen + 0x6634);
    }
}
