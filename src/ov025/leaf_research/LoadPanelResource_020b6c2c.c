#include "nitro/types.h"

typedef struct PanelSource {
    u8 pad_00[0xc];
    int resourceId;
} PanelSource;

typedef struct ResourcePanel {
    u8 pad_00[4];
    PanelSource *source;
    BOOL asyncLoad;
    u32 field;
} ResourcePanel;

typedef char *(*PathResolver)(int resourceId);

extern void *QueueFileLoadRequest_020ba114(char *path, int loadMode, void *callback, void *userData);
extern void ApplyTagAndMarkEntryReady_020b6c0c(u32 owner, u32 entry);
extern void *func_0202c48c(char *path, u32 heapId);
extern void func_ov025_020b6ab8(ResourcePanel *panel, void *data, u32 field);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void LoadPanelResource_020b6c2c(ResourcePanel *panel, PathResolver resolvePath)
{
    char *path = resolvePath(panel->source->resourceId);
    void *data;

    if (panel->asyncLoad) {
        QueueFileLoadRequest_020ba114(path, 1, ApplyTagAndMarkEntryReady_020b6c0c, panel);
        return;
    }
    data = func_0202c48c(path, 14);
    func_ov025_020b6ab8(panel, data, panel->field);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(data);
}
