#include "nitro/types.h"

typedef struct StreamReader {
    u8 block[2][0x200];
    u8 uncompContext[0x14];
    u8 curBlock;
    u8 prevBlock;
    u8 pad_416[2];
    s32 blockLen[2];
} StreamReader;

typedef struct FileLoader {
    StreamReader *reader;
} FileLoader;

extern FileLoader data_02060564;

extern s32 ReadFileSync_0200b674(void *file, void *buffer, s32 length);
extern int func_0200b6c8(void *file, void *buffer, s32 length);
extern void *AllocFromHeapOrDefaultEx_0202a210(u32 size, int align, void **heap);
extern void func_02005750(void *context, u8 *dest, const void *header);
extern int func_02005794(void *context, void *src, int len);

u8 *StartStreamUncompress_0202b894(StreamReader *reader, void *file, u8 *dest, s32 *sizeInOut, void **heap,
                                   BOOL alignFromEnd, int unused, BOOL *done)
{
    s32 size;
    StreamReader *loaderReader = data_02060564.reader;

    reader->blockLen[0] = ReadFileSync_0200b674(file, reader, 0x200);
    size = *(u32 *)reader->block[0] >> 8;
    if (dest == NULL) {
        if (alignFromEnd) {
            dest = AllocFromHeapOrDefaultEx_0202a210(size, -0x20, heap);
        } else {
            dest = AllocFromHeapOrDefaultEx_0202a210(size, 0x20, heap);
        }
    } else if (size > *sizeInOut) {
        return NULL;
    }
    *sizeInOut = size;
    func_02005750(reader->uncompContext, dest, reader);
    loaderReader->blockLen[0] -= 4;
    *done = func_02005794(loaderReader->uncompContext, loaderReader->block[0] + 4, loaderReader->blockLen[0]) == 0;
    if (*done == FALSE) {
        reader->curBlock = 0;
        reader->prevBlock = 1;
        reader->blockLen[1] = 0;
        reader->blockLen[0] = 0;
        reader->blockLen[reader->curBlock] = func_0200b6c8(file, reader->block[reader->curBlock], 0x200);
    }
    return dest;
}
