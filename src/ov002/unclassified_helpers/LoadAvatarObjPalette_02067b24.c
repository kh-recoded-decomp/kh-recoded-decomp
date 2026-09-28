#include "nitro/types.h"

typedef struct {
    int format;
    BOOL isExtendedPalette;
    u32 sizeBytes;
    u8 *rawData;
} PaletteData;

typedef struct {
    int format;
    BOOL isExtendedPalette;
    u32 vramAddress[3];
} PaletteProxy;

extern char data_ov002_0206c438[];
extern void G2D_InitializePaletteProxy_020152b8(PaletteProxy *proxy);
extern BOOL G2D_GetPaletteFromFile_02014d84(void *nclrFile, PaletteData **outPalette);
extern void func_020154fc(PaletteData *palette, u32 vramOffset, int vramType, PaletteProxy *proxy);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void *func_0202c478(u32 fileId, u32 flags);
extern int func_0202cc6c(const char *path, u32 kind, u32 fromTop);
extern void ZeroHalfThenFree_0202cd78(int handle);
extern void func_0202d314(void *archive, int extra);
extern void *func_0202d3e0(void *archive, int recordIndex, int entryIndex);

void LoadAvatarObjPalette_02067b24(BOOL useSubScreen)
{
    int fileHandle;
    void *archive;
    void *nclrFile;
    int vramType;
    PaletteData *palette;
    PaletteProxy proxy;

    G2D_InitializePaletteProxy_020152b8(&proxy);
    fileHandle = func_0202cc6c(data_ov002_0206c438, 0x10, 0);
    archive = func_0202c478((fileHandle + 0x8000U & 0xfffffc) << 7 | 0x80000000, 0x10);
    vramType = 1;
    func_0202d314(archive, 1);
    nclrFile = func_0202d3e0(archive, 0, 0);
    if (nclrFile != NULL) {
        G2D_GetPaletteFromFile_02014d84(nclrFile, &palette);
        if (palette->isExtendedPalette) {
            palette->sizeBytes -= 0x200;
            if (useSubScreen) {
                vramType = 2;
            }
            palette->rawData += 0x200;
            func_020154fc(palette, 0x200, vramType, &proxy);
        }
    }
    if (archive != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(archive);
    }
    ZeroHalfThenFree_0202cd78(fileHandle);
}
