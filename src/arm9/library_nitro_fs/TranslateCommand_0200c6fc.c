#include "nitro/types.h"

#define RESULT_SUCCESS 0
#define RESULT_FAILURE 1
#define RESULT_UNSUPPORTED 4
#define RESULT_PROC_ASYNC 0x100
#define RESULT_PROC_DEFAULT 0x101
#define RESULT_PROC_UNKNOWN 0x102
#define COMMAND_COUNT 13

struct File;

typedef int (*ArchiveProcFunc)(struct File *file, u32 command);
typedef int (*DefaultCommandFunc)(struct File *file);

typedef struct ArchiveContext {
    u8 pad_00[0x2c];
    ArchiveProcFunc proc;
    u32 procFlag;
} ArchiveContext;

typedef struct Archive {
    u8 pad_00[0x20];
    ArchiveContext *context;
} Archive;

typedef struct File {
    u8 pad_00[8];
    Archive *arc;
} File;

extern DefaultCommandFunc const data_020529ac[];
extern int func_0200a2a4(File *file, int result);

int TranslateCommand_0200c6fc(File *file, u32 command, BOOL blocking)
{
    int result = RESULT_PROC_DEFAULT;
    ArchiveContext *const context = file->arc->context;
    const int bit = 1 << command;

    if ((context->procFlag & bit) != 0) {
        result = context->proc(file, command);
        switch (result) {
        case RESULT_SUCCESS:
        case RESULT_FAILURE:
        case RESULT_UNSUPPORTED:
            break;
        case RESULT_PROC_ASYNC:
            break;
        case RESULT_PROC_UNKNOWN:
            result = RESULT_PROC_DEFAULT;
            context->procFlag &= ~bit;
            break;
        }
    }
    if (result == RESULT_PROC_DEFAULT) {
        if (command < COMMAND_COUNT) {
            result = data_020529ac[command](file);
        } else {
            result = RESULT_UNSUPPORTED;
        }
    }
    if (blocking) {
        result = func_0200a2a4(file, result);
    }
    return result;
}
