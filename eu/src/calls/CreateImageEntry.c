#include "nitro/types.h"

typedef struct ImagePaletteProxy {
    u32 format;
    BOOL extendedPalette;
    u32 vramAddresses[3];
} ImagePaletteProxy;

typedef struct ImageProxy {
    u32 vramAddresses[3];
    u32 sizeS;
    u32 sizeT;
    u32 format;
    BOOL extendedPalette;
    u32 transparentColor;
    u32 mappingType;
} ImageProxy;

typedef struct ImageInfo {
    u32 format;
    u32 width;
    u32 height;
    void *cellBank;
    void *animBank;
} ImageInfo;

typedef struct ImageEntry {
    BOOL active;
    ImageInfo info;
    void *cellFile;
    void *animFile;
    void *archive;
    ImagePaletteProxy palette;
    ImageProxy image;
    u32 blockCount;
    struct ImageEntry *next;
    s16 paletteSlot;
    u16 reserved66;
} ImageEntry;

typedef struct ImageManager {
    u8 reserved0000[0x4618];
    ImageEntry *head;
    ImageEntry entries[64];
} ImageManager;

extern int FindFreeElementIndex(ImageManager *manager);
extern void MI_CpuFill8(void *destination, u8 value, u32 size);
extern void NNS_G2dInitImageProxy(ImageProxy *proxy);
extern void NNS_G2dInitImagePaletteProxy(ImagePaletteProxy *proxy);
extern void DispObj_LoadImage(ImageManager *manager, int fileId, ImageEntry *image);
extern int DecodeStateAt4604(ImageManager *manager);
extern u32 NNS_G2dGetImageLocation(const ImageProxy *proxy, int vramType);

/* Loads an image entry and links it between neighbouring VRAM addresses. */
int CreateImageEntry(ImageManager *manager, int fileId)
{
    ImageEntry *entry;
    int index = FindFreeElementIndex(manager);
    entry = &manager->entries[index];

    MI_CpuFill8(entry, 0, sizeof(*entry));
    entry->active = TRUE;
    NNS_G2dInitImageProxy(&entry->image);
    NNS_G2dInitImagePaletteProxy(&entry->palette);
    DispObj_LoadImage(manager, fileId, entry);
    entry->next = NULL;
    if (manager->head == NULL) {
        manager->head = entry;
    } else {
        int vramType = DecodeStateAt4604(manager);
        ImageEntry *current;
        u32 address = NNS_G2dGetImageLocation(&entry->image, vramType);
        current = manager->head;

        while (current != NULL) {
            if (current->next == NULL) {
                current->next = entry;
                break;
            }
            u32 currentAddress = NNS_G2dGetImageLocation(&current->image, vramType);
            u32 nextAddress = NNS_G2dGetImageLocation(&current->next->image, vramType);
            if (currentAddress < address && address < nextAddress) {
                entry->next = current->next;
                current->next = entry;
                break;
            }
            current = current->next;
        }
    }
    return index;
}
