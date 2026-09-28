#include "nitro/types.h"
#include "nitro/fs.h"

#define FS_RESULT_INVALID_PARAMETER ((FSResult)6)
#define FS_RESULT_NO_ENTRY ((FSResult)11)

extern FSResult FSi_TranslateCommand_0200c6fc(FSFile *file, FSCommandType command, BOOL blocking);
extern int FSi_IncrementSjisPositionToSlash_0200b2c8(const char *path, int pos);
extern void SetFieldAndDispatch_0200be64(FSFile *file, u32 id);

static inline int FSi_StrNICmp(const char *str1, const char *str2, u32 len)
{
    int ret = 0;
    u32 i;
    for (i = 0; i < len; ++i) {
        u32 c1 = (u8)(str1[i] - 'A');
        u32 c2 = (u8)(str2[i] - 'A');
        if (c1 <= 'Z' - 'A') {
            c1 += 'a' - 'A';
        }
        if (c2 <= 'Z' - 'A') {
            c2 += 'a' - 'A';
        }
        ret = (int)(c1 - c2);
        if (ret != 0) {
            break;
        }
    }
    return ret;
}

FSResult FSi_FindPathCommand_0200c058(FSFile *dir)
{
    const char *path = dir->arg.findpath.path;
    const BOOL findDirectory = dir->arg.findpath.find_directory;

    (void)FSi_TranslateCommand_0200c6fc(dir, FS_COMMAND_SEEKDIR, TRUE);
    for (; *path; path += (*path ? 1 : 0)) {
        int nameLen = FSi_IncrementSjisPositionToSlash_0200b2c8(path, 0);
        u32 isDirectory = ((path[nameLen] != '\0') || findDirectory);
        if (!nameLen) {
            return FS_RESULT_INVALID_PARAMETER;
        } else if (*path == '.') {
            if (nameLen == 1) {
                path += 1;
                continue;
            } else if ((nameLen == 2) && (path[1] == '.')) {
                if (dir->prop.dir.pos.own_id != 0) {
                    SetFieldAndDispatch_0200be64(dir, dir->prop.dir.parent);
                }
                path += 2;
                continue;
            }
        } else if (*path == '*') {
            break;
        }
        if (nameLen > FS_FILE_NAME_MAX) {
            return FS_RESULT_NO_ENTRY;
        } else {
            FSDirEntry entry;
            dir->arg.readdir.p_entry = &entry;
            dir->arg.readdir.skip_string = FALSE;
            for (;;) {
                if (FSi_TranslateCommand_0200c6fc(dir, FS_COMMAND_READDIR, TRUE) != FS_RESULT_SUCCESS) {
                    return FS_RESULT_NO_ENTRY;
                }
                if ((isDirectory == entry.is_directory) && (nameLen == entry.name_len)
                    && (FSi_StrNICmp(path, entry.name, (u32)nameLen) == 0)) {
                    if (isDirectory) {
                        path += nameLen;
                        dir->arg.seekdir.pos = entry.dir_id;
                        (void)FSi_TranslateCommand_0200c6fc(dir, FS_COMMAND_SEEKDIR, TRUE);
                        break;
                    } else if (findDirectory) {
                        return FS_RESULT_NO_ENTRY;
                    } else {
                        *dir->arg.findpath.result.file = entry.file_id;
                        return FS_RESULT_SUCCESS;
                    }
                }
            }
        }
    }
    if (!findDirectory) {
        return FS_RESULT_NO_ENTRY;
    } else {
        *dir->arg.findpath.result.dir = dir->prop.dir.pos;
        return FS_RESULT_SUCCESS;
    }
}
