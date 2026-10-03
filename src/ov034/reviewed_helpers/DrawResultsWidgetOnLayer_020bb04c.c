#include "nitro/types.h"

typedef struct ResultsWork {
    u8 pad_0000[0x64d8];
    u8 screenLayers[0x1c];
} ResultsWork;

typedef struct ResultsScreen {
    void *params;
    ResultsWork *work;
} ResultsScreen;

extern ResultsScreen g_resultsScreen_020c0f80;
extern void func_ov027_020b9a74(void *layers, void *widget);

void DrawResultsWidgetOnLayer_020bb04c(void *widget)
{
    func_ov027_020b9a74(g_resultsScreen_020c0f80.work->screenLayers, widget);
}
