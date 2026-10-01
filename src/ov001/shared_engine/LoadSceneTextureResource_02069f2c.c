#include "nitro/types.h"

typedef struct TextureResource {
    u8 pad_00[0x20];
    u16 texInfoFlags;
} TextureResource;

typedef struct SceneTextureState {
    u8 pad_00[0x20];
    u32 texSize;
    u32 plttSize;
    u32 texKey;
    u32 plttKey;
} SceneTextureState;

extern SceneTextureState *data_ov001_020a0480;
extern u32 (*data_02055c4c)(u32 size, BOOL is4x4comp, u32 opt);
extern u32 (*data_02055c54)(u32 size, BOOL is4pltt, u32 opt);

extern void func_0202c690(int enable);
extern TextureResource *FindTextureResourceBlock_0201ac70(void *file);
extern u32 GetTextureImageBytes_020188cc(TextureResource *tex);
extern u32 GetPaletteBytes_02018964(TextureResource *tex);
extern void ReleaseTextureResourceKeys_020188f4(TextureResource *tex, u32 texKey, u32 tex4x4Key);
extern void func_02018978(TextureResource *tex, u32 plttKey);
extern void Tex_LoadVram_0202d14c(TextureResource *tex);
extern void func_0202d204(TextureResource *tex);

void LoadSceneTextureResource_02069f2c(void *file)
{
    SceneTextureState *state = data_ov001_020a0480;
    TextureResource *tex;
    u32 texSize;
    u32 plttSize;

    func_0202c690(0);
    tex = FindTextureResourceBlock_0201ac70(file);
    texSize = GetTextureImageBytes_020188cc(tex);
    plttSize = GetPaletteBytes_02018964(tex);
    if (state->texKey == 0) {
        state->texKey = data_02055c4c(texSize, FALSE, 0);
    }
    if (state->plttKey == 0) {
        state->plttKey = data_02055c54(plttSize, tex->texInfoFlags & 0x8000, 0);
    }
    ReleaseTextureResourceKeys_020188f4(tex, state->texKey, 0);
    func_02018978(tex, state->plttKey);
    Tex_LoadVram_0202d14c(tex);
    func_0202d204(tex);
    state->texSize = texSize;
    state->plttSize = plttSize;
    func_0202c690(1);
}
