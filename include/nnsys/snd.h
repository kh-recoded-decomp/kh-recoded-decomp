/* NitroSystem sound: archive, players, heaps, streams, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NNSYS_SND_H
#define NNSYS_SND_H

#include "nitro/types.h"
#include "nitro/os.h"
#include "nitro/spi.h"
#include "nitro/fs.h"
#include "nitro/snd.h"
#include "nnsys/fnd.h"

struct AdpcmState;
struct NNSSndArc;
struct NNSSndArcBankInfo;
struct NNSSndArcFat;
struct NNSSndArcFileInfo;
struct NNSSndArcHeader;
struct NNSSndArcInfo;
struct NNSSndArcOffsetTable;
struct NNSSndArcPlayerInfo;
struct NNSSndArcSeqArcInfo;
struct NNSSndArcSeqInfo;
struct NNSSndArcStrmCallbackInfo;
struct NNSSndArcStrmCallbackParam;
struct NNSSndArcStrmInfo;
struct NNSSndArcStrmPlayerInfo;
struct NNSSndArcSymbol;
struct NNSSndArcWaveArcInfo;
struct NNSSndFader;
struct NNSSndHandle;
struct NNSSndHeap;
struct NNSSndHeapBlock;
struct NNSSndHeapSection;
struct NNSSndPlayer;
struct NNSSndPlayerHeap;
struct NNSSndSeqArc;
struct NNSSndSeqArcSeqInfo;
struct NNSSndSeqData;
struct NNSSndSeqParam;
struct NNSSndSeqPlayer;
struct NNSSndStrm;
struct NNSSndStrmChannel;
struct NNSSndStrmData;
struct NNSSndStrmHandle;
struct NNSSndStrmPlayer;
struct NNSSndStrmThread;
struct SNDBinaryBlockHeader;
struct SNDBinaryFileHeader;

typedef struct NNSSndHeap *NNSSndHeapHandle;

typedef void (*NNSSndHeapDisposeCallback)(void *mem, u32 size, u32 data1, u32 data2);

typedef enum NNSSndStrmFormat {
    NNS_SND_STRM_FORMAT_PCM8,
    NNS_SND_STRM_FORMAT_PCM16
} NNSSndStrmFormat;

typedef enum NNSSndStrmCallbackStatus {
    NNS_SND_STRM_CALLBACK_SETUP,
    NNS_SND_STRM_CALLBACK_INTERVAL
} NNSSndStrmCallbackStatus;

typedef void (*NNSSndStrmCallback)(NNSSndStrmCallbackStatus status, int numChannles, void * buffer[], u32 len, NNSSndStrmFormat format, void * arg);

typedef struct NNSSndStrm {
    NNSFndLink link;
    PMSleepCallbackInfo preSleepInfo;
    PMSleepCallbackInfo postSleepInfo;
    NNSSndStrmFormat format;
    BOOL activeFlag :1;
    BOOL startFlag :1;
    u32 chBufLen;
    int interval;
    NNSSndStrmCallback callback;
    void * callbackArg;
    int curBuffer;
    int volume;
    int alarmNo;
    u32 chBitMask;
    int numChannels;
    u8 channelNo[16 ];
} NNSSndStrm;

typedef enum NNSSndArcStrmCallbackStatus {
    NNS_SND_ARC_STRM_CALLBACK_DATA_END
} NNSSndArcStrmCallbackStatus;

typedef struct NNSSndArcStrmCallbackInfo {
    int playerNo;
    int strmNo;
} NNSSndArcStrmCallbackInfo;

typedef struct NNSSndArcStrmCallbackParam {
    int strmNo;
    u32 offset;
} NNSSndArcStrmCallbackParam;

typedef BOOL (*NNSSndArcStrmCallback)(NNSSndArcStrmCallbackStatus status, const NNSSndArcStrmCallbackInfo * info, NNSSndArcStrmCallbackParam * param, void * arg);

typedef struct NNSSndStrmHandle {
    struct NNSSndStrmPlayer * player;
} NNSSndStrmHandle;

typedef struct NNSSndStrmThread {
    OSThread thread;
    u64 stack[ 1024 / sizeof(u64) ];
    OSThreadQueue threadQ;
    OSMutex mutex;
    NNSFndList commandList;
} NNSSndStrmThread;

typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;

typedef BOOL (*OpenStreamFunc)(struct NNSSndStrmPlayer * player, u32 fileId);

typedef void (*CloseStreamFunc)(struct NNSSndStrmPlayer * player);

typedef s32 (*ReadStreamFunc)(struct NNSSndStrmPlayer * player, void * dest, u32 size, u32 offset);

typedef void (*CancelStreamFunc)(struct NNSSndStrmPlayer * player);

typedef struct NNSSndStrmData {
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;
    u8 format;
    u8 loopFlag;
    u8 numChannels;
    u8 pad_;
    u16 sampleRate;
    u16 timer;
    u32 loopStart;
    u32 loopEnd;
    u32 dataOffset;
    u32 numBlocks;
    u32 blockSize;
    u32 blockSamples;
    u32 lastBlockSize;
    u32 lastBlockSamples;
} NNSSndStrmData;

typedef struct AdpcmState {
    s16 prevSample;
    u8 prevIndex;
    u8 padding;
} AdpcmState;

typedef struct NNSSndStrmPlayer {
    NNSSndStrm stream;
    FSFile file;
    u32 fileOffset;
    NNSSndStrmData info;
    NNSSndFader fader;
    AdpcmState adpcmState[6 ];
    BOOL activeFlag  : 1;
    BOOL playFlag    : 1;
    BOOL startFlag   : 1;
    BOOL fadeOutFlag : 1;
    BOOL dirtyFlag   : 1;
    BOOL finishFlag  : 1;
    BOOL monoFlag    : 1;
    volatile int finishCounter;
    volatile BOOL prepareFlag;
    volatile int commandCount;
    int allocChannelCount;
    u8 numChannels;
    u8 padding;
    u8 chNoList[6 ];
    void * buffer;
    u32 bufSize;
    NNSSndStrmCallback strmCallback;
    void * strmCallbackArg;
    NNSSndArcStrmCallback sndArcStrmCallback;
    void * sndArcStrmCallbackArg;
    int strmNo;
    int playerNo;
    NNSSndStrmHandle * handle;
    int prio;
    int initVolume;
    int extVolume;
    int volume;
    u32 curSample;
    OpenStreamFunc openStreamFunc;
    CloseStreamFunc closeStreamFunc;
    ReadStreamFunc readStreamFunc;
    CancelStreamFunc cancelStreamFunc;
} NNSSndStrmPlayer;

typedef struct NNSSndArcFileInfo {
    u32 offset;
    u32 size;
    void * mem;
    u32 reserved;
} NNSSndArcFileInfo;

typedef struct NNSSndArcFat {
    struct SNDBinaryBlockHeader blockHeader;
    u32 count;
    NNSSndArcFileInfo files[0];
} NNSSndArcFat;

typedef struct NNSSndArcInfo {
    struct SNDBinaryBlockHeader blockHeader;
    u32 seqOffset;
    u32 seqArcOffset;
    u32 bankOffset;
    u32 waveArcOffset;
    u32 playerInfoOffset;
    u32 groupInfoOffset;
    u32 strmPlayerInfoOffset;
    u32 strmOffset;
} NNSSndArcInfo;

typedef struct NNSSndArcSymbol {
    struct SNDBinaryBlockHeader blockHeader;
    u32 seqOffset;
    u32 seqArcOffset;
    u32 bankOffset;
    u32 waveArcOffset;
    u32 playerOffset;
    u32 groupOffset;
    u32 strmPlayerOffset;
    u32 strmOffset;
} NNSSndArcSymbol;

typedef struct NNSSndArcHeader {
    struct SNDBinaryFileHeader fileHeader;
    u32 symbolDataOffset;
    u32 symbolDataSize;
    u32 infoOffset;
    u32 infoSize;
    u32 fatOffset;
    u32 fatSize;
    u32 fileImageOffset;
    u32 fileImageSize;
} NNSSndArcHeader;

typedef struct NNSSndArc {
    NNSSndArcHeader header;
    BOOL file_open;
    FSFile file;
    FSFileID fileId;
    struct NNSSndArcFat * fat;
    struct NNSSndArcSymbol * symbol;
    struct NNSSndArcInfo * info;
    s32 loadBlockSize;
} NNSSndArc;

typedef struct NNSSndHandle {
    struct NNSSndSeqPlayer * player;
} NNSSndHandle;

typedef struct NNSSndSeqPlayer {
    struct NNSSndHandle * handle;
    struct NNSSndPlayer * player;
    struct NNSSndPlayerHeap * heap;
    NNSFndLink playerLink;
    NNSFndLink prioLink;
    NNSSndFader fader;
    u8 status;
    u8 startFlag;
    u8 pauseFlag;
    u8 prepareFlag;
    u32 commandTag;
    u16 seqType;
    u16 pad2;
    u16 seqNo;
    u16 seqArcIndex;
    u8 playerNo;
    u8 prio;
    s16 volume;
    u8 initVolume;
    u8 extVolume;
    u16 pad3_;
} NNSSndSeqPlayer;

typedef struct NNSSndPlayer {
    NNSFndList playerList;
    NNSFndList heapList;
    u32 playableSeqCount;
    u32 allocChBitFlag;
    u8 volume;
    u8 pad_;
    u16 pad2_;
} NNSSndPlayer;

typedef struct NNSSndPlayerHeap {
    NNSFndLink link;
    NNSSndHeapHandle handle;
    NNSSndSeqPlayer * player;
    int playerNo;
} NNSSndPlayerHeap;

typedef enum NNSSndPlayerSeqType {
    NNS_SND_PLAYER_SEQ_TYPE_INVALID,
    NNS_SND_PLAYER_SEQ_TYPE_SEQ,
    NNS_SND_PLAYER_SEQ_TYPE_SEQARC
} NNSSndPlayerSeqType;

#define NNS_SND_SEQ_ARC_INVALID_OFFSET 0xffffffff

typedef struct NNSSndSeqParam {
    u16 bankNo;
    u8 volume;
    u8 channelPrio;
    u8 playerPrio;
    u8 playerNo;
    u16 reserved;
} NNSSndSeqParam;

typedef struct NNSSndSeqArcSeqInfo {
    u32 offset;
    struct NNSSndSeqParam param;
} NNSSndSeqArcSeqInfo;

typedef struct NNSSndSeqArc {
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;
    u32 baseOffset;
    u32 count;
    NNSSndSeqArcSeqInfo info[0];
} NNSSndSeqArc;

#define NNS_SND_STRM_THREAD_STACK_SIZE 1024

enum NNSSndSeqPlayerStatus {
    NNS_SND_SEQ_PLAYER_STATUS_STOP,
    NNS_SND_SEQ_PLAYER_STATUS_PLAY,
    NNS_SND_SEQ_PLAYER_STATUS_FADEOUT
};

typedef struct NNSSndHeap {
    NNSFndHeapHandle handle;
    NNSFndList sectionList;
} NNSSndHeap;

typedef struct NNSSndHeapSection {
    NNSFndList blockList;
    NNSFndLink link;
} NNSSndHeapSection;

typedef struct NNSSndSeqData {
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;
    u32 baseOffset;
    u32 data[0];
} NNSSndSeqData;

typedef struct NNSSndArcBankInfo {
    u32 fileId;
    u16 waveArcNo[4 ];
} NNSSndArcBankInfo;

typedef struct NNSSndArcOffsetTable {
    u32 count;
    u32 offset[0];
} NNSSndArcOffsetTable;

typedef struct NNSSndArcPlayerInfo {
    u8 seqMax;
    u8 padding;
    u16 allocChBitFlag;
    u32 heapSize;
} NNSSndArcPlayerInfo;

typedef struct NNSSndArcSeqArcInfo {
    u32 fileId;
} NNSSndArcSeqArcInfo;

typedef struct NNSSndArcSeqInfo {
    u32 fileId;
    struct NNSSndSeqParam param;
} NNSSndArcSeqInfo;

typedef struct NNSSndArcStrmInfo {
    u32 fileId;
    u8 volume;
    u8 playerPrio;
    u8 playerNo;
    u8 flags;
} NNSSndArcStrmInfo;

typedef struct NNSSndArcStrmPlayerInfo {
    u8 numChannels;
    u8 chNoList[2];
} NNSSndArcStrmPlayerInfo;

typedef struct NNSSndArcWaveArcInfo {
    u32 fileId :24;
    u32 flags  :8;
} NNSSndArcWaveArcInfo;

#define NNS_SND_ARC_LOAD_ALL 0xff

typedef enum NNSSndArcLoadResult {
    NNS_SND_ARC_LOAD_SUCESS = 0,
    NNS_SND_ARC_LOAD_ERROR_INVALID_GROUP_NO,
    NNS_SND_ARC_LOAD_ERROR_INVALID_SEQ_NO,
    NNS_SND_ARC_LOAD_ERROR_INVALID_SEQARC_NO,
    NNS_SND_ARC_LOAD_ERROR_INVALID_BANK_NO,
    NNS_SND_ARC_LOAD_ERROR_INVALID_WAVEARC_NO,
    NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_SEQ,
    NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_SEQARC,
    NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_BANK,
    NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_WAVE
} NNSSndArcLoadResult;

#define NNS_SND_HEAP_INVALID_HANDLE NNS_FND_HEAP_INVALID_HANDLE

#define NNS_SND_PLAYER_NUM 32

#define NNS_SND_STRM_PLAYER_NUM 4

typedef struct NNSSndHeapBlock {
    NNSFndLink link;
    u32 size;
    NNSSndHeapDisposeCallback callback;
    u32 data1;
    u32 data2;
    u8 padding[ 0x20 - ((sizeof(NNSFndLink) + sizeof(NNSSndHeapDisposeCallback) + sizeof(u32) * 3) & 0x1f) ];
    u32 buffer[ 0 ];
} NNSSndHeapBlock;

typedef struct NNSSndStrmChannel {
    void * buffer;
    int volume;
} NNSSndStrmChannel;

#define NNS_SND_ARC_LOAD_BANK (1 << 1)

#define NNS_SND_ARC_LOAD_WAVE (1 << 2)

#define NNS_SND_ARC_INVALID_WAVEARC_NO 0xffff

#define NNS_SND_ARC_BANK_TO_WAVEARC_NUM 4

#define NNS_SND_ARC_WAVEARC_SINGLE_LOAD (1 << 0)

#define NNS_SND_ARC_LOAD_SEQ (1 << 0)

#define NNS_SND_ARC_LOAD_SEQARC (1 << 3)

typedef enum {
    NNS_SND_CAPTURE_FORMAT_PCM16,
    NNS_SND_CAPTURE_FORMAT_PCM8
} NNSSndCaptureFormat;

typedef enum {
    NNS_SND_CAPTURE_TYPE_REVERB,
    NNS_SND_CAPTURE_TYPE_EFFECT,
    NNS_SND_CAPTURE_TYPE_SAMPLING
} NNSSndCaptureType;

typedef void (*NNSSndCaptureCallback)(void * bufferL, void * bufferR, u32 len, NNSSndCaptureFormat format, void * arg);

#define NNS_SND_ARC_STRM_FORCE_STEREO (1 << 0)

#define NNS_SND_STRM_CHANNEL_MAX 16

#endif
