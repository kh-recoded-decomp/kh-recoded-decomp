#include "nitro/types.h"

#define FS_COMMAND_FINDPATH 4

typedef struct RomFileId {
    void *arc;
    u32 fileId;
} RomFileId;

typedef struct RomDirPos {
    void *arc;
    u16 ownId;
    u16 index;
    u32 pos;
} RomDirPos;

typedef struct RomFile {
    struct RomFile *next;
    void *userdata;
    void *arc;
    u32 stat;
    u8 pad_10[0x20];
    RomDirPos findPos;
    const char *findPath;
    BOOL findDirectory;
    void *findResult;
} RomFile;

extern void func_0200b394(RomFile *file);
extern int func_0200c6fc(RomFile *file, int command, BOOL blocking);

int FSi_ROMFAT_FindPath_0200c9d4(void *arc, u32 baseDirId, const char *path, u32 *targetId, BOOL targetIsDirectory)
{
    int result;
    union {
        RomFileId file;
        RomDirPos dir;
    } target;
    RomFile file;

    func_0200b394(&file);
    file.arc = arc;
    file.findPos.arc = arc;
    file.findPos.ownId = (u16)baseDirId;
    file.findPos.index = 0;
    file.findPos.pos = 0;
    file.findPath = path;
    file.findDirectory = targetIsDirectory;
    file.findResult = &target;
    result = func_0200c6fc(&file, FS_COMMAND_FINDPATH, TRUE);
    if (result == 0) {
        if (targetIsDirectory) {
            *targetId = target.dir.ownId;
        } else {
            *targetId = target.file.fileId;
        }
    }
    return result;
}
