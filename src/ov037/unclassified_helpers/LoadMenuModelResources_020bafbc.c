#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Ov037ContextView {
    u8 pad_000[0x70];
    u8 model[0xa4];
    VecFx32 cameraOffset;
    u8 pad_120[0x54];
    u8 animation[0x80];
} Ov037ContextView;

extern Ov037ContextView *g_ov037Context_020bb764;
extern const VecFx32 g_menuCameraOffset_020bb630;
extern char g_menuArchivePath_020bb704[];
extern char g_menuModelName_020bb714[];
extern char g_menuAnimName_020bb728[];
extern void *func_0202c48c(char *path, u32 flags);
extern void func_0202ed3c(void *dst, char *name, void *info, int flags);
extern BOOL func_0202e9ec(void *dst, void *src, char *name, int flags);
extern void selectJointAnimationBlend_0202f2cc(void *model, u16 trackIndex, void *animation, int blend);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void LoadMenuModelResources_020bafbc(void)
{
    VecFx32 offset = g_menuCameraOffset_020bb630;
    void *archive;
    int track;

    archive = func_0202c48c(g_menuArchivePath_020bb704, 0xe);
    func_0202ed3c(g_ov037Context_020bb764->model, g_menuModelName_020bb714, archive, 0xe);
    func_0202e9ec(g_ov037Context_020bb764->animation, g_ov037Context_020bb764->model, g_menuAnimName_020bb728, 0xe);
    for (track = 0; track < 5; track++) {
        selectJointAnimationBlend_0202f2cc(g_ov037Context_020bb764->model, track, g_ov037Context_020bb764->animation, 0);
    }
    g_ov037Context_020bb764->cameraOffset = offset;
    NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
}
