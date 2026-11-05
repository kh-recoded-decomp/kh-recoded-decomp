#ifndef EU_FILE_LOAD_QUEUE_H
#define EU_FILE_LOAD_QUEUE_H

#include "nitro/types.h"

typedef struct FileLoadRequest FileLoadRequest;
typedef void (*FileLoadCallback)(FileLoadRequest *request, void *userData);
typedef int (*FileLoadQueueStep)(void);

typedef struct FileLoadLink {
    void *prevObject;
    void *nextObject;
} FileLoadLink;

typedef struct FileLoadList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} FileLoadList;

typedef struct FileLoadQueueWork {
    FileLoadList pending;
    FileLoadList completed;
} FileLoadQueueWork;

struct FileLoadRequest {
    s32 state;
    char *pathOrId; /* Bit 31 set: encoded file ID; otherwise an owned path copy. */
    void *buffer;
    s32 loadMode;
    void *userData;
    FileLoadCallback callback;
    FileLoadLink link;
    u8 unknown20[4];
};

typedef char FileLoadListSizeCheck[sizeof(FileLoadList) == 12 ? 1 : -1];
typedef char FileLoadQueueWorkSizeCheck[sizeof(FileLoadQueueWork) == 24 ? 1 : -1];
typedef char FileLoadRequestSizeCheck[sizeof(FileLoadRequest) == 36 ? 1 : -1];

/* Preserve the original source-owned storage spans. Only the first word of the seven-word
 * state is interpreted here, as a 32-bit DS work address. The remaining
 * six words have no established meaning. The descriptor's first five words
 * are established; its remaining six words are retained zero storage.
 */
extern u32 gFileLoadQueueStateWords[7];
extern void *gFileLoadQueueTaskDescriptor[11];

static inline FileLoadQueueWork *FileLoadQueues_GetWork(void)
{
    return (FileLoadQueueWork *)gFileLoadQueueStateWords[0];
}

FileLoadQueueStep InitFileLoadQueueTask(void *userData);
int UpdateFileLoadQueueTask(void);
void *GetFileLoadRequestBuffer(const FileLoadRequest *request);
FileLoadRequest *QueueFileLoadRequest(char *pathOrId, s32 loadMode,
                                    FileLoadCallback callback, void *userData);
void ProcessFileLoadQueue(void);
BOOL IsFileLoadQueueEmpty(void);
void DestroyFileLoadRequest(FileLoadRequest *request, BOOL freeBuffer);
void ClearOverlayLoadQueues(void);

#endif
