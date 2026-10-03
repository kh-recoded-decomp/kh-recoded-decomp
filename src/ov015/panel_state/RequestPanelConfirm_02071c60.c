#include "nitro/types.h"

typedef struct PanelContext {
    u8 pad_00[0xe0];
    u8 flags;
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern u32 DispatchContextCommand_02066c78(u32 command, u32 value, u32 extra, void *buffer);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void RequestPanelConfirm_02071c60(void)
{
    data_ov015_0207e960->flags |= 4;
    if (DispatchContextCommand_02066c78(5, 0, 0, NULL) != 0) {
        PlaySoundEffect_0204d924(2, 0xd);
    }
}
