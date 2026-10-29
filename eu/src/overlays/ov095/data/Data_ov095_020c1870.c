#include "nitro/types.h"

#pragma explicit_zero_data on

extern void CloseEntryDetail(void);
extern void ConfirmGridMoveA(void);
extern void ConfirmGridMoveB(void);
extern void OpenEntryDetail(void);
extern void ShowNextEntry(void);
extern void ShowPreviousEntry(void);
extern void UpdatePanelFrame(void);
extern void InitGridMenu(void);
extern void ShutdownItemReport(void);
extern void ItemReport_ReturnToParentMenu(void);
extern void ItemReport_ReturnToRootMenu(void);

void *gItemReportMenuCallbacks[17] = {
    (void *)InitGridMenu,
    (void *)ShutdownItemReport,
    (void *)UpdatePanelFrame,
    (void *)0x00000006,
    (void *)0x0001150C,
    (void *)ConfirmGridMoveA,
    (void *)ConfirmGridMoveB,
    (void *)ShowPreviousEntry,
    (void *)ShowNextEntry,
    NULL,
    (void *)ItemReport_ReturnToParentMenu,
    NULL,
    NULL,
    (void *)CloseEntryDetail,
    (void *)OpenEntryDetail,
    NULL,
    (void *)ItemReport_ReturnToRootMenu,
};
