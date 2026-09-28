#include "nitro/types.h"

struct FSArchive;

typedef struct FSFile {
    struct FSFile *next;
    void *userdata;
    struct FSArchive *arc;
    u32 stat;
    void *argument;
} FSFile;

typedef struct FSArchiveProcs {
    int (*readFile)(struct FSArchive *arc, FSFile *file, void *buffer, u32 *length);
    int (*writeFile)(struct FSArchive *arc, FSFile *file, void *buffer, u32 *length);
    int (*seekDirectory)(struct FSArchive *arc, FSFile *file, u32 id, u32 position);
    int (*readDirectory)(struct FSArchive *arc, FSFile *file, void *info);
    int (*findPath)(struct FSArchive *arc, u32 baseId, const char *path, u32 *targetId, BOOL targetIsDirectory);
    int (*getPath)(struct FSArchive *arc, FSFile *file, BOOL isDirectory, char *buffer, u32 *length);
    int (*openFileFast)(struct FSArchive *arc, FSFile *file, u32 id, u32 mode);
    int (*openFileDirect)(struct FSArchive *arc, FSFile *file, u32 top, u32 bottom, u32 *id);
    int (*closeFile)(struct FSArchive *arc, FSFile *file);
    void (*activate)(struct FSArchive *arc);
    void (*idle)(struct FSArchive *arc);
    void (*suspend)(struct FSArchive *arc);
    void (*resume)(struct FSArchive *arc);
    int (*openFile)(struct FSArchive *arc, FSFile *file, u32 baseId, const char *path, u32 mode);
    int (*seekFile)(struct FSArchive *arc, FSFile *file, int *offset, int from);
    int (*getFileLength)(struct FSArchive *arc, FSFile *file, u32 *length);
    int (*getFilePosition)(struct FSArchive *arc, FSFile *file, u32 *position);
    void (*mount)(struct FSArchive *arc);
    void (*unmount)(struct FSArchive *arc);
    int (*getArchiveCaps)(struct FSArchive *arc, u32 *caps);
    int (*createFile)(struct FSArchive *arc, u32 baseId, const char *path, u32 permit);
    int (*deleteFile)(struct FSArchive *arc, u32 baseId, const char *path);
    int (*renameFile)(struct FSArchive *arc, u32 baseIdSrc, const char *pathSrc, u32 baseIdDst, const char *pathDst);
    int (*getPathInfo)(struct FSArchive *arc, u32 baseId, const char *path, void *info);
    int (*setPathInfo)(struct FSArchive *arc, u32 baseId, const char *path, void *info);
    int (*createDirectory)(struct FSArchive *arc, u32 baseId, const char *path, u32 permit);
    int (*deleteDirectory)(struct FSArchive *arc, u32 baseId, const char *path);
    int (*renameDirectory)(struct FSArchive *arc, u32 baseIdSrc, const char *pathSrc, u32 baseIdDst, const char *pathDst);
    int (*getArchiveResource)(struct FSArchive *arc, void *resource);
    void *unused_74;
    int (*flushFile)(struct FSArchive *arc, FSFile *file);
    int (*setFileLength)(struct FSArchive *arc, FSFile *file, u32 length);
    int (*openDirectory)(struct FSArchive *arc, FSFile *file, u32 baseId, const char *path, u32 mode);
    int (*closeDirectory)(struct FSArchive *arc, FSFile *file);
    int (*setSeekCache)(struct FSArchive *arc, FSFile *file, void *buffer, u32 size);
} FSArchiveProcs;

typedef struct FSArchive {
    u8 pad_00[0x24];
    const FSArchiveProcs *procs;
} FSArchive;

typedef struct { void *buffer; u32 length; } ArgBuffer;
typedef struct { u32 first; u32 second; } ArgPair;
typedef struct { void *ptr; } ArgPtr;
typedef struct { u32 value; } ArgValue;
typedef struct { u32 baseId; const char *path; u32 targetId; BOOL targetIsDirectory; } ArgFindPath;
typedef struct { BOOL isDirectory; char *buffer; u32 length; } ArgGetPath;
typedef struct { u32 id; u32 top; u32 bottom; } ArgOpenDirect;
typedef struct { u32 baseId; const char *path; u32 mode; } ArgPathMode;
typedef struct { u32 baseId; const char *path; void *info; } ArgPathInfo;
typedef struct { int offset; int from; } ArgSeek;
typedef struct { u32 baseId; const char *path; } ArgPath;
typedef struct { u32 baseIdSrc; const char *pathSrc; u32 baseIdDst; const char *pathDst; } ArgRename;

extern BOOL func_0200a1d8(int command);
extern void func_0200a200(FSFile *file, int result);
extern int func_0200a2a4(FSFile *file, int result);

int FSi_InvokeCommand_0200a2fc(FSFile *file, u32 command) {
    int result;
    FSArchive *const arc = file->arc;
    {
        const FSArchiveProcs *procs = arc->procs;
        if (command >= 0x23) {
            result = 4;
        } else if (((void *const *)procs)[command] == NULL) {
            result = 4;
        } else {
            switch (command) {
            case 0: {
                ArgBuffer *arg = (ArgBuffer *)file->argument;
                result = procs->readFile(arc, file, arg->buffer, &arg->length);
                break;
            }
            case 1: {
                ArgBuffer *arg = (ArgBuffer *)file->argument;
                result = procs->writeFile(arc, file, arg->buffer, &arg->length);
                break;
            }
            case 2: {
                ArgPair *arg = (ArgPair *)file->argument;
                result = procs->seekDirectory(arc, file, arg->first, arg->second);
                break;
            }
            case 3: {
                ArgPtr *arg = (ArgPtr *)file->argument;
                result = procs->readDirectory(arc, file, arg->ptr);
                break;
            }
            case 4: {
                ArgFindPath *arg = (ArgFindPath *)file->argument;
                result = procs->findPath(arc, arg->baseId, arg->path, &arg->targetId, arg->targetIsDirectory);
                break;
            }
            case 5: {
                ArgGetPath *arg = (ArgGetPath *)file->argument;
                result = procs->getPath(arc, file, arg->isDirectory, arg->buffer, &arg->length);
                break;
            }
            case 6: {
                ArgPair *arg = (ArgPair *)file->argument;
                result = procs->openFileFast(arc, file, arg->first, arg->second);
                break;
            }
            case 7: {
                ArgOpenDirect *arg = (ArgOpenDirect *)file->argument;
                result = procs->openFileDirect(arc, file, arg->top, arg->bottom, &arg->id);
                break;
            }
            case 8:
                result = procs->closeFile(arc, file);
                break;
            case 9:
                procs->activate(arc);
                return 0;
            case 10:
                procs->idle(arc);
                return 0;
            case 11:
                procs->suspend(arc);
                return 0;
            case 12:
                procs->resume(arc);
                return 0;
            case 13: {
                ArgPathMode *arg = (ArgPathMode *)file->argument;
                result = procs->openFile(arc, file, arg->baseId, arg->path, arg->mode);
                break;
            }
            case 14: {
                ArgSeek *arg = (ArgSeek *)file->argument;
                result = procs->seekFile(arc, file, &arg->offset, arg->from);
                break;
            }
            case 15: {
                ArgValue *arg = (ArgValue *)file->argument;
                result = procs->getFileLength(arc, file, &arg->value);
                break;
            }
            case 16: {
                ArgValue *arg = (ArgValue *)file->argument;
                result = procs->getFilePosition(arc, file, &arg->value);
                break;
            }
            case 17:
                procs->mount(arc);
                return 0;
            case 18:
                procs->unmount(arc);
                return 0;
            case 19: {
                ArgValue *arg = (ArgValue *)file->argument;
                result = procs->getArchiveCaps(arc, &arg->value);
                break;
            }
            case 20: {
                ArgPathMode *arg = (ArgPathMode *)file->argument;
                result = procs->createFile(arc, arg->baseId, arg->path, arg->mode);
                break;
            }
            case 21: {
                ArgPath *arg = (ArgPath *)file->argument;
                result = procs->deleteFile(arc, arg->baseId, arg->path);
                break;
            }
            case 22: {
                ArgRename *arg = (ArgRename *)file->argument;
                result = procs->renameFile(arc, arg->baseIdSrc, arg->pathSrc, arg->baseIdDst, arg->pathDst);
                break;
            }
            case 23: {
                ArgPathInfo *arg = (ArgPathInfo *)file->argument;
                result = procs->getPathInfo(arc, arg->baseId, arg->path, arg->info);
                break;
            }
            case 24: {
                ArgPathInfo *arg = (ArgPathInfo *)file->argument;
                result = procs->setPathInfo(arc, arg->baseId, arg->path, arg->info);
                break;
            }
            case 25: {
                ArgPathMode *arg = (ArgPathMode *)file->argument;
                result = procs->createDirectory(arc, arg->baseId, arg->path, arg->mode);
                break;
            }
            case 26: {
                ArgPath *arg = (ArgPath *)file->argument;
                result = procs->deleteDirectory(arc, arg->baseId, arg->path);
                break;
            }
            case 27: {
                ArgRename *arg = (ArgRename *)file->argument;
                result = procs->renameDirectory(arc, arg->baseIdSrc, arg->pathSrc, arg->baseIdDst, arg->pathDst);
                break;
            }
            case 28: {
                ArgPtr *arg = (ArgPtr *)file->argument;
                result = procs->getArchiveResource(arc, arg->ptr);
                break;
            }
            case 30:
                result = procs->flushFile(arc, file);
                break;
            case 31: {
                ArgValue *arg = (ArgValue *)file->argument;
                result = procs->setFileLength(arc, file, arg->value);
                break;
            }
            case 32: {
                ArgPathMode *arg = (ArgPathMode *)file->argument;
                result = procs->openDirectory(arc, file, arg->baseId, arg->path, arg->mode);
                break;
            }
            case 33:
                result = procs->closeDirectory(arc, file);
                break;
            case 34: {
                ArgBuffer *arg = (ArgBuffer *)file->argument;
                result = procs->setSeekCache(arc, file, arg->buffer, arg->length);
                break;
            }
            default:
                result = 4;
                break;
            }
        }
    }
    if (!func_0200a1d8(command)) {
        if ((file->stat & 4) != 0) {
            result = func_0200a2a4(file, result);
        } else if (result != 0x100) {
            func_0200a200(file, result);
        }
    }
    return result;
}
