/* Stores the playable sequence count for a player number in the global player table.
 * Uncertainty: The source of the count and player role are not shown. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nns/snd/calls/func_02019dd0.c.
 * Original routine: func_02019dd0. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000




typedef struct {
    void * headObject;
    void * tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;
typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
struct NNSSndPlayer;
typedef struct NNSSndPlayer {
    NNSFndList playerList;
    NNSFndList heapList;
    u32 playableSeqCount;
    u32 allocChBitFlag;
    u8 volume;
    u8 pad_;
    u16 pad2_;
} NNSSndPlayer;
extern NNSSndPlayer data_0205dcf8[ 32 ];

/* func_0201d414 -- NitroSystem player.c: NNS_SndPlayerSetPlayableSeqCount. */
void func_0201d414 (int playerNo, int seqCount)
{

    data_0205dcf8[ playerNo ].playableSeqCount = (u16)seqCount;
}
