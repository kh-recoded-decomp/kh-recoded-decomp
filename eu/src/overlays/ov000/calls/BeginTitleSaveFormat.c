#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x66dc];
    u64 formatStartTick;
    BOOL formatResult;
} Panel;

extern void func_ov000_02061fc0(Panel *owner, int noticeType);
extern u64 OS_GetTick(void);
extern BOOL FormatSaveData(void);

void BeginTitleSaveFormat(Panel *panel)
{
    func_ov000_02061fc0(panel, 0);
    panel->formatStartTick = OS_GetTick();
    panel->formatResult = FormatSaveData();
}
