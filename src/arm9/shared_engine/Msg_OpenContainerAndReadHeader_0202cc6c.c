#include "nitro/types.h"

typedef struct MsgContainerHeader {
    u16 signature;
    u16 countAndFlags;
    u32 mode;
    u32 fileStart;
    u32 dataOffset;
} MsgContainerHeader;

typedef struct FSFile {
    u8 pad_00[8];
    u32 fileStart;
    u8 pad_0c[0x24 - 0xc];
    u32 imageBase;
    u8 pad_28[0x48 - 0x28];
} FSFile;

extern void func_0200b394(FSFile *file);
extern void FSi_WaitForCardThread_01ff8140(void);
extern char *Msg_BuildLangPath_0202b798(const char *src);
extern int CallSelectionHandler_0200b740(FSFile *file, const char *path);
extern s32 ReadFileSync_0200b674(FSFile *file, void *buffer, s32 length);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void func_0200b5b0(FSFile *file);

MsgContainerHeader *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd)
{
    FSFile file;
    MsgContainerHeader header;
    u16 count;
    u16 size;
    MsgContainerHeader *container;

    func_0200b394(&file);
    FSi_WaitForCardThread_01ff8140();
    CallSelectionHandler_0200b740(&file, Msg_BuildLangPath_0202b798(name));
    ReadFileSync_0200b674(&file, &header, sizeof(header));

    {
        u16 countAndFlags = header.countAndFlags;
        u16 evenCount;

        count = countAndFlags & 0x1ff;
        evenCount = (count + 1) / 2 * 2;
        size = (u16)(evenCount * 2 + count * 4);
        if (countAndFlags & 0x8000) {
            size = (u16)(size + (u16)(count * 8));
        }
    }

    if (allocFromEnd) {
        container = NNSi_FndAllocFromDefaultHeapEx_0202a19c((u16)(size + sizeof(MsgContainerHeader)), -4);
    } else {
        container = NNSi_FndAllocFromDefaultHeapEx_0202a19c((u16)(size + sizeof(MsgContainerHeader)), 4);
    }
    *container = header;
    container->mode = mode;
    container->fileStart = file.fileStart;
    container->dataOffset = container->dataOffset + file.imageBase;
    ReadFileSync_0200b674(&file, container + 1, size);
    func_0200b5b0(&file);
    return container;
}
