#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x66dc];
    u64 formatStartTick;
    BOOL formatResult;
} Panel;

extern void ShowTitleNotice_02061fc0(Panel *owner, int noticeType);
extern u64 OS_GetTick_02003fd4(void);
extern BOOL FormatSaveData_02026ea0(void);

void BeginTitleSaveFormat_02062f44(Panel *panel)
{
    ShowTitleNotice_02061fc0(panel, 0);
    panel->formatStartTick = OS_GetTick_02003fd4();
    panel->formatResult = FormatSaveData_02026ea0();
}
