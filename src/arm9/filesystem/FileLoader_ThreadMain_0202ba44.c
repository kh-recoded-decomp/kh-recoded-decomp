#include "nitro/types.h"

typedef struct OSThreadQueue {
    struct OSThread *head;
    struct OSThread *tail;
} OSThreadQueue;

typedef struct LoaderRequest {
    struct LoaderRequest *next;
    int type;
    union {
        struct {
            void *archive;
            u32 imageTop;
            u32 imageBottom;
        } file;
        struct {
            u16 dataId;
            u16 waveId;
            void *heap;
            u8 *statusOut;
        } snd;
    } u;
    u8 uncompressContext[0x28 - 0x14];
    u8 *dest;
    u32 size;
} LoaderRequest;

typedef struct LoaderBlockFlags {
    u8 cur : 1;
    u8 prev : 1;
    u8 first : 1;
} LoaderBlockFlags;

typedef struct LoaderReader {
    u8 block[2][0x200];
    u8 file[0x48];
    LoaderRequest *request;
    OSThreadQueue idleQueue;
    int blockLen[2];
    LoaderBlockFlags flags;
} LoaderReader;

typedef struct FileLoader {
    void *reader;
    LoaderReader *reader2;
    u8 pad_08[0x3c - 0x8];
    int hold;
} FileLoader;

extern FileLoader data_02060564;
extern u8 message_queue_02060584[];

extern void OS_WakeupThread_02002af8(OSThreadQueue *queue);
extern BOOL OS_ReceiveMessage_02002ff8(void *queue, void *msg, int flags);
extern BOOL func_0200b494(void *file, void *archive, u32 imageTop, u32 imageBottom, u32 fileIndex);
extern void FSi_WaitForCardThread_01ff8140(void);
extern int func_0200b674(void *file, void *dst, int len);
extern int func_0200b6c8(void *file, void *dst, int len);
extern void RunResetCallbackAndIdle_02004cf0(void);
extern int func_02005794(void *context, void *src, int len);
extern void func_0200b1e4(void *file);
extern void func_0200b5b0(void *file);
extern void func_020033e0(void);
extern void func_0200344c(void *buffer, u32 size);
extern void OS_RescheduleThread_02002bb4(void);
extern void NNS_SndArcLoadSeq_0201f318(u32 dataId, void *heap);
extern BOOL NNS_SndArcLoadSeq_0201f348(u32 dataId, void *heap);
extern BOOL NNS_SndArcLoadSeq_0201f378(u32 waveId, void *heap);
extern void *func_0204df80(u32 dataId);
extern BOOL func_02020240(void *handle, u32 waveId, int flags);
extern void func_0202b86c(LoaderRequest *request);

static inline void FlushLoaded(void *buffer, u32 size)
{
    if (size >= 0x2400) {
        func_020033e0();
    } else {
        func_0200344c(buffer, size);
    }
}

void FileLoader_ThreadMain_0202ba44(void *arg)
{
    int state = 0;
    LoaderRequest *request;
    LoaderReader *reader = data_02060564.reader2;

    for (;;) {
        switch (state) {
        case 0:
            if (data_02060564.hold == 0) {
                OS_WakeupThread_02002af8(&reader->idleQueue);
                reader->request = 0;
            }
            OS_ReceiveMessage_02002ff8(message_queue_02060584, &reader->request, 1);
            if (reader->request == 0) {
                return;
            }
            reader->blockLen[1] = 0;
            reader->blockLen[0] = 0;
            request = reader->request;
            switch (request->type) {
            case 0:
                func_0200b494(reader->file, request->u.file.archive, request->u.file.imageTop, request->u.file.imageBottom, 0);
                state = 4;
                break;
            case 1:
                func_0200b494(reader->file, request->u.file.archive, request->u.file.imageTop, request->u.file.imageBottom, 0);
                state = 2;
                break;
            case 2:
                state = 5;
                break;
            case 3:
                state = 6;
                break;
            case 4:
                state = 7;
                break;
            }
            break;
        case 2:
            reader->flags.cur = 0;
            reader->flags.prev = 1;
            reader->flags.first = 1;
            FSi_WaitForCardThread_01ff8140();
            reader->blockLen[reader->flags.cur] = func_0200b674(reader->file, reader->block[reader->flags.cur], 0x200);
            state = 3;
            break;
        case 3:
            reader->flags.cur ^= 1;
            reader->flags.prev ^= 1;
            FSi_WaitForCardThread_01ff8140();
            reader->blockLen[reader->flags.cur] = func_0200b6c8(reader->file, reader->block[reader->flags.cur], 0x200);
            if (reader->blockLen[reader->flags.prev] == 0) {
                break;
            }
            if (reader->blockLen[reader->flags.prev] == -1) {
                RunResetCallbackAndIdle_02004cf0();
            }
            {
                u8 *src = reader->block[reader->flags.prev];
                int len = reader->blockLen[reader->flags.prev];

                if (reader->flags.first) {
                    src += 4;
                    len -= 4;
                    reader->flags.first = 0;
                }
                if (func_02005794(request->uncompressContext, src, len) == 0) {
                    func_0200b1e4(reader->file);
                    func_0200b5b0(reader->file);
                    FlushLoaded(request->dest, request->size);
                    state = 8;
                }
            }
            func_0200b1e4(reader->file);
            OS_RescheduleThread_02002bb4();
            break;
        case 4:
            FSi_WaitForCardThread_01ff8140();
            reader->blockLen[0] = func_0200b674(reader->file, request->dest + reader->blockLen[1], 0x200);
            if (reader->blockLen[0] == -1) {
                RunResetCallbackAndIdle_02004cf0();
            } else {
                reader->blockLen[1] += reader->blockLen[0];
                if (reader->blockLen[1] >= (int)request->size) {
                    func_0200b5b0(reader->file);
                    state = 8;
                }
            }
            OS_RescheduleThread_02002bb4();
            break;
        case 5:
            FSi_WaitForCardThread_01ff8140();
            NNS_SndArcLoadSeq_0201f318(request->u.snd.dataId, request->u.snd.heap);
            *request->u.snd.statusOut = 2;
            state = 8;
            OS_RescheduleThread_02002bb4();
            break;
        case 6:
            FSi_WaitForCardThread_01ff8140();
            if (NNS_SndArcLoadSeq_0201f348(request->u.snd.dataId, request->u.snd.heap) != 0) {
                FSi_WaitForCardThread_01ff8140();
                *request->u.snd.statusOut = NNS_SndArcLoadSeq_0201f378(request->u.snd.waveId, request->u.snd.heap) ? 2 : 3;
            } else {
                *request->u.snd.statusOut = 3;
            }
            state = 8;
            OS_RescheduleThread_02002bb4();
            break;
        case 7:
            FSi_WaitForCardThread_01ff8140();
            if (func_02020240(func_0204df80(request->u.snd.dataId), request->u.snd.waveId, 0) != 0) {
                *request->u.snd.statusOut = 2;
            } else {
                *request->u.snd.statusOut = 3;
            }
            state = 8;
            OS_RescheduleThread_02002bb4();
            break;
        case 8:
            func_0202b86c(request);
            state = 0;
            break;
        }
    }
}
