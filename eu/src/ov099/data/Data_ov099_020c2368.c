#include "nitro/types.h"

#pragma explicit_zero_data on

extern void HandleListCursorUp(void);
extern void UpdateModelViewerScreen(void);
extern void InitEnemyViewerScreen(void);
extern void DestroyEnemyViewerScreen(void);

void *data_ov099_020c2368[6] = {
    (void *)InitEnemyViewerScreen,
    (void *)DestroyEnemyViewerScreen,
    (void *)UpdateModelViewerScreen,
    (void *)0x00000008,
    (void *)0x0000D6F8,
    (void *)HandleListCursorUp,
};
