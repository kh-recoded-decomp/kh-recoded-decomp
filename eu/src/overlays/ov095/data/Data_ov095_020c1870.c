#include "nitro/types.h"

#pragma explicit_zero_data on

extern void CloseEntryDetail(void);
extern void ConfirmGridMoveA(void);
extern void ConfirmGridMoveB(void);
extern void OpenEntryDetail(void);
extern void ShowNextEntry(void);
extern void ShowPreviousEntry(void);
extern void UpdatePanelFrame(void);
extern void func_ov095_020beb20(void);
extern void func_ov095_020bed84(void);
extern void func_ov095_020befd4(void);
extern void func_ov095_020beffc(void);

void *gItemReportMenuCallbacks[17] = {
    (void *)func_ov095_020beb20,
    (void *)func_ov095_020bed84,
    (void *)UpdatePanelFrame,
    (void *)0x00000006,
    (void *)0x0001150C,
    (void *)ConfirmGridMoveA,
    (void *)ConfirmGridMoveB,
    (void *)ShowPreviousEntry,
    (void *)ShowNextEntry,
    NULL,
    (void *)func_ov095_020befd4,
    NULL,
    NULL,
    (void *)CloseEntryDetail,
    (void *)OpenEntryDetail,
    NULL,
    (void *)func_ov095_020beffc,
};
