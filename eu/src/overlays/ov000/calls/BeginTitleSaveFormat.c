#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x66dc];
    u64 formatStartTick;
    BOOL formatResult;
} Panel;

extern void ShowTitleNotice(Panel *owner, int noticeType);
extern u64 OS_GetTick(void);
extern BOOL FormatSaveData(void);

void BeginTitleSaveFormat(Panel *panel)
{
    ShowTitleNotice(panel, 0);
    panel->formatStartTick = OS_GetTick();
    panel->formatResult = FormatSaveData();
}
