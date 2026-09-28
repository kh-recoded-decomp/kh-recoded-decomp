#include "nitro/types.h"

typedef struct RomRegion {
    u32 offset;
    u32 length;
} RomRegion;

typedef struct FileID {
    void *arc;
    u32 fileId;
} FileID;

typedef struct File {
    u8 pad_00[0x48];
} File;

typedef struct OverlayInfo {
    u8 header[0x20];
    int target;
    RomRegion filePos;
} OverlayInfo;

extern RomRegion data_02057b04;
extern RomRegion data_02057b0c;

extern u8 *func_0200913c(void);
extern void func_0200b394(File *file);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern FileID MakeTypeTagPair_0200b824(const OverlayInfo *info);
extern BOOL OpenFileFast_0200b4d4(File *file, FileID id);
extern BOOL func_0200d530(File *file, u32 top, u32 bottom);
extern s32 ReadFileSync_0200b674(File *file, void *buffer, s32 length);
extern BOOL func_0200b5b0(File *file);
extern u32 func_0200d2a4(File *file);
extern u32 func_0200b5f0(File *file);

BOOL LoadOverlayInfo_0200b850(OverlayInfo *info, int target, u32 id)
{
    BOOL result = FALSE;
    const u32 pos = id * 0x20;
    const RomRegion *region;

    region = (target == 0) ? &data_02057b04 : &data_02057b0c;
    if (region->offset != 0) {
        if (pos < region->length) {
            File file[1];

            func_0200b394(file);
            MI_CpuCopy8_01ff89a8((const void *)(region->offset + pos), info, 0x20);
            info->target = target;
            if (OpenFileFast_0200b4d4(file, MakeTypeTagPair_0200b824(info))) {
                info->filePos.offset = func_0200d2a4(file);
                info->filePos.length = func_0200b5f0(file);
                func_0200b5b0(file);
                result = TRUE;
            }
        }
    } else {
        region = (target == 0) ? (const RomRegion *)(func_0200913c() + 0x50)
                               : (const RomRegion *)(func_0200913c() + 0x58);
        if (pos < region->length) {
            File file[1];

            func_0200b394(file);
            if (func_0200d530(file, region->offset + pos, region->offset + region->length)) {
                if (ReadFileSync_0200b674(file, info, 0x20) != 0x20) {
                    func_0200b5b0(file);
                } else {
                    func_0200b5b0(file);
                    info->target = target;
                    if (OpenFileFast_0200b4d4(file, MakeTypeTagPair_0200b824(info))) {
                        info->filePos.offset = func_0200d2a4(file);
                        info->filePos.length = func_0200b5f0(file);
                        func_0200b5b0(file);
                        result = TRUE;
                    }
                }
            }
        }
    }
    return result;
}
