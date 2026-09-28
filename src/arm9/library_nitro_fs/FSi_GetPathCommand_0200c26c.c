#include "nitro/types.h"
#include "nitro/fs.h"

#define FS_RESULT_NO_ENTRY ((FSResult)11)
#define INVALID_ID 0x10000

extern FSResult FSi_TranslateCommand_0200c6fc(FSFile *file, FSCommandType command, BOOL blocking);
extern void func_0200b394(FSFile *file);
extern const char *ResolveTaggedPointer_0200b034(FSArchive *arc);
extern int Strlen_02010c74(const char *str);
extern void SetFieldAndDispatch_0200be64(FSFile *file, u32 id);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern const char data_02055c30[];

static inline BOOL IsDirectory(volatile const FSFile *file)
{
    return (file->stat & FS_FILE_STATUS_IS_DIR) ? TRUE : FALSE;
}

FSResult FSi_GetPathCommand_0200c26c(FSFile *file)
{
    FSArchive *const arc = file->arc;
    FSGetPathInfo *info = &file->arg.getpath;
    FSDirEntry entry;
    FSFile cursor;
    u32 dirId;
    u32 fileId;

    func_0200b394(&cursor);
    cursor.arc = arc;

    if (IsDirectory(file)) {
        dirId = file->prop.dir.pos.own_id;
        fileId = INVALID_ID;
    } else {
        fileId = file->prop.file.own_id;
        {
            u32 pos = 0;
            u32 dirCount = 0;
            dirId = INVALID_ID;
            do {
                SetFieldAndDispatch_0200be64(&cursor, pos);
                if (!pos) {
                    dirCount = cursor.prop.dir.parent;
                }
                cursor.arg.readdir.p_entry = &entry;
                cursor.arg.readdir.skip_string = TRUE;
                while (FSi_TranslateCommand_0200c6fc(&cursor, FS_COMMAND_READDIR, TRUE) == FS_RESULT_SUCCESS) {
                    if (!entry.is_directory && (entry.file_id.file_id == fileId)) {
                        dirId = cursor.prop.dir.pos.own_id;
                        break;
                    }
                }
            } while ((dirId == INVALID_ID) && (++pos < dirCount));
        }
    }

    if (dirId == INVALID_ID) {
        info->total_len = 0;
        return FS_RESULT_NO_ENTRY;
    }

    {
        u32 id = dirId;
        int total = Strlen_02010c74(ResolveTaggedPointer_0200b034(arc)) + 2;
        SetFieldAndDispatch_0200be64(&cursor, id);
        if (fileId != INVALID_ID) {
            total += entry.name_len;
        }
        while (id != 0) {
            SetFieldAndDispatch_0200be64(&cursor, cursor.prop.dir.parent);
            cursor.arg.readdir.p_entry = &entry;
            cursor.arg.readdir.skip_string = TRUE;
            while (FSi_TranslateCommand_0200c6fc(&cursor, FS_COMMAND_READDIR, TRUE) == FS_RESULT_SUCCESS) {
                if (entry.is_directory && (entry.dir_id.own_id == id)) {
                    total += entry.name_len + 1;
                    break;
                }
            }
            id = cursor.prop.dir.pos.own_id;
        }
        info->total_len = (u16)(total + 1);
        info->dir_id = (u16)dirId;
    }

    if (info->buf != NULL && info->buf_len >= info->total_len) {
        u8 *dst = info->buf;
        u32 total = info->total_len;
        u32 pos = 0;
        u32 id = dirId;
        {
            const char *arcName = ResolveTaggedPointer_0200b034(arc);
            int len = Strlen_02010c74(arcName);
            MI_CpuCopy8_01ff89a8(arcName, dst + pos, (u32)len);
            pos += len;
            MI_CpuCopy8_01ff89a8(data_02055c30, dst + pos, 2);
            pos += 2;
        }
        SetFieldAndDispatch_0200be64(&cursor, id);
        if (fileId != INVALID_ID) {
            cursor.arg.readdir.p_entry = &entry;
            cursor.arg.readdir.skip_string = FALSE;
            while (FSi_TranslateCommand_0200c6fc(&cursor, FS_COMMAND_READDIR, TRUE) == FS_RESULT_SUCCESS) {
                if (!entry.is_directory && (entry.file_id.file_id == fileId)) {
                    break;
                }
            }
            {
                u32 len = entry.name_len + 1;
                MI_CpuCopy8_01ff89a8(entry.name, dst + total - len, len);
                total -= len;
            }
        } else {
            dst[total - 1] = '\0';
            total -= 1;
        }
        while (id != 0) {
            SetFieldAndDispatch_0200be64(&cursor, cursor.prop.dir.parent);
            cursor.arg.readdir.p_entry = &entry;
            cursor.arg.readdir.skip_string = FALSE;
            dst[total - 1] = '/';
            total -= 1;
            while (FSi_TranslateCommand_0200c6fc(&cursor, FS_COMMAND_READDIR, TRUE) == FS_RESULT_SUCCESS) {
                if (entry.is_directory && (entry.dir_id.own_id == id)) {
                    u32 len = entry.name_len;
                    MI_CpuCopy8_01ff89a8(entry.name, dst + total - len, len);
                    total -= len;
                    break;
                }
            }
            id = cursor.prop.dir.pos.own_id;
        }
    }
    return FS_RESULT_SUCCESS;
}
