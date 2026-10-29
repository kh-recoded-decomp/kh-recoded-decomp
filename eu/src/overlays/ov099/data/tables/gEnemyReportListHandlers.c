#include "nitro/types.h"

extern void HandleListCursorDown(void); /* HandleListCursorDown */
extern void HandleListPageUp(void);
extern void HandleListPageDown(void); /* HandleListPageDown */
extern void EnemyReport_ReturnToParentMenu(void);
extern void CloseSubBgPanel(void);
extern void OpenSubBgPanel(void);
extern void EnemyReport_ReturnToRootMenu(void);

void (*gEnemyReportListHandlers[11])(void) = {
    HandleListCursorDown, /* HandleListCursorDown */
    HandleListPageUp,
    HandleListPageDown, /* HandleListPageDown */
    NULL,
    EnemyReport_ReturnToParentMenu,
    NULL,
    NULL,
    CloseSubBgPanel,
    OpenSubBgPanel,
    NULL,
    EnemyReport_ReturnToRootMenu,
};
