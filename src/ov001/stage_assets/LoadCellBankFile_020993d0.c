#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 imageTop;
    u8 pad_0c[0x24 - 0x0c];
    u32 position;
    u8 pad_28[0x48 - 0x28];
} FileHandle;

typedef struct {
    u16 unk_00;
    u16 info;
    u32 fileId;
    u32 imageTop;
    u32 dataOffset;
} CellBankHeader;

extern void func_0200b394(FileHandle *file);
extern void FSi_WaitForCardThread_01ff8140(void);
extern BOOL openFileFromNitroRomArchive_0202ce60(FileHandle *file, u32 fileId);
extern s32 ReadFileSync_0200b674(FileHandle *file, void *buffer, s32 length);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern BOOL func_0200b5b0(FileHandle *file);

CellBankHeader *LoadCellBankFile_020993d0(u32 fileId, u32 tag, BOOL fromTail) {
    CellBankHeader header;
    FileHandle file;
    CellBankHeader *bank;
    u16 size;
    u16 length;
    u16 count;

    func_0200b394(&file);
    FSi_WaitForCardThread_01ff8140();
    openFileFromNitroRomArchive_0202ce60(&file, fileId);
    ReadFileSync_0200b674(&file, &header, sizeof(header));
    count = header.info & 0x1ff;
    length = (u16)((count + 1) / 2 * 2);
    length = length * 2 + count * 4;
    if (header.info & 0x8000) {
        length += (u16)(count * 8);
    }
    size = length + sizeof(header);
    if (fromTail) {
        bank = NNSi_FndAllocFromDefaultHeapEx_0202a19c(size, -4);
    } else {
        bank = NNSi_FndAllocFromDefaultHeapEx_0202a19c(size, 4);
    }
    *bank = header;
    bank->fileId = tag;
    bank->imageTop = file.imageTop;
    bank->dataOffset += file.position;
    ReadFileSync_0200b674(&file, bank + 1, length);
    func_0200b5b0(&file);
    return bank;
}
