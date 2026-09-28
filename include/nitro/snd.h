/* Sound: the ARM9's side of the sound driver, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NITRO_SND_H
#define NITRO_SND_H

#include "nitro/types.h"

struct SNDBankData;
struct SNDBinaryBlockHeader;
struct SNDBinaryFileHeader;
struct SNDCommand;
struct SNDCommandMgr;
struct SNDDrumSet;
struct SNDExChannel;
struct SNDInstData;
struct SNDInstParam;
struct SNDInstPos;
struct SNDKeySplit;
struct SNDLfo;
struct SNDLfoParam;
struct SNDSharedWork;
struct SNDWaveArc;
struct SNDWaveArcLink;
struct SNDWaveData;
struct SNDWaveParam;

#define SND_BANK_TO_WAVEARC_MAX 4

#define SND_INST_KEYSPLIT_MAX 8

typedef enum SNDInstType {
    SND_INST_INVALID = 0,
    SND_INST_PCM = 0x01,
    SND_INST_PSG,
    SND_INST_NOISE,
    SND_INST_DIRECTPCM,
    SND_INST_NULL,
    SND_INST_DRUM_SET = 0x10,
    SND_INST_KEY_SPLIT
} SNDInstType;

typedef struct SNDBinaryFileHeader {
    char signature[4];
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} SNDBinaryFileHeader;

typedef struct SNDBinaryBlockHeader {
    u32 kind;
    u32 size;
} SNDBinaryBlockHeader;

typedef struct SNDWaveArcLink {
    struct SNDWaveArc *waveArc;
    struct SNDWaveArcLink *next;
} SNDWaveArcLink;

typedef struct SNDInstParam {
    u16 wave[2];
    u8 original_key;
    u8 attack;
    u8 decay;
    u8 sustain;
    u8 release;
    u8 pan;
} SNDInstParam;

typedef struct SNDInstData {
    u8 type;
    u8 padding_;
    struct SNDInstParam param;
} SNDInstData;

typedef struct SNDKeySplit {
    u8 key[SND_INST_KEYSPLIT_MAX];
    struct SNDInstData instOffset[0];
} SNDKeySplit;

typedef struct SNDDrumSet {
    u8 min;
    u8 max;
    struct SNDInstData instOffset[0];
} SNDDrumSet;

typedef struct SNDInstPos {
    u32 prgNo;
    u32 index;
} SNDInstPos;

#define SND_VOLUME_DB_MIN (-723)

#define SND_VOLUME_DB_MAX 0

#define SND_VOLUME_TABLE_SIZE (SND_VOLUME_DB_MAX - SND_VOLUME_DB_MIN + 1)

typedef struct SNDCommand {
    struct SNDCommand *next;      /* 0x00 */
    u32 id;                       /* 0x04 */
    u32 arg[4];                   /* 0x08 */
} SNDCommand;

typedef struct SNDSharedWork SNDSharedWork;

#define SND_COMMAND_NUM 256

#define SND_PXI_FIFO_MESSAGE_BUFSIZE 8

#define SND_COMMAND_NOBLOCK 0

#define SND_COMMAND_BLOCK 1

typedef struct SNDWaveData SNDWaveData;

#define SND_VOLUME_SHIFT_2_MIN (-240)

#define SND_VOLUME_SHIFT_1_MIN (-120)

#define SND_VOLUME_SHIFT_0_MIN (-60)

typedef struct SNDCommandMgr {
    SNDCommand *freeHead;
    unsigned int processedTag;
    SNDCommand *reservedHead;
    SNDCommand *reservedTail;
    SNDCommand *freeTail;
    unsigned int unk14;
    int sentRingIndex;
    int sentBlockCount;
    unsigned int nextTag;
} SNDCommandMgr;

typedef void (*SNDAlarmHandler)(void *arg);

typedef enum {
    SND_DUTY_1_8,
    SND_DUTY_2_8,
    SND_DUTY_3_8,
    SND_DUTY_4_8,
    SND_DUTY_5_8,
    SND_DUTY_6_8,
    SND_DUTY_7_8
} SNDDuty;

typedef enum SNDExChannelCallbackStatus {
    SND_EX_CHANNEL_CALLBACK_DROP,
    SND_EX_CHANNEL_CALLBACK_FINISH
} SNDExChannelCallbackStatus;

typedef void (*SNDExChannelCallback) (struct SNDExChannel * ch_p, SNDExChannelCallbackStatus status, void * userData);

typedef struct SNDWaveParam {
        u8 format;
        u8 loopflag;
        u16 rate;
        u16 timer;
        u16 loopstart;
        u32 looplen;
    } SNDWaveParam;

typedef struct SNDLfoParam {
    u8 target;
    u8 speed;
    u8 depth;
    u8 range;
    u16 delay;
} SNDLfoParam;

typedef struct SNDLfo {
    struct SNDLfoParam param;
    u16 delay_counter;
    u16 counter;
} SNDLfo;

typedef struct SNDExChannel {
    u8 myNo;
    u8 type;
    u8 env_status;
    u8 active_flag : 1;
    u8 start_flag : 1;
    u8 auto_sweep : 1;
    u8 sync_flag : 5;
    u8 pan_range;
    u8 original_key;
    s16 user_decay2;
    u8 key;
    u8 velocity;
    s8 init_pan;
    s8 user_pan;
    s16 user_decay;
    s16 user_pitch;
    s32 env_decay;
    s32 sweep_counter;
    s32 sweep_length;
    u8 attack;
    u8 sustain;
    u16 decay;
    u16 release;
    u8 prio;
    u8 pan;
    u16 volume;
    u16 timer;
    struct SNDLfo lfo;
    s16 sweep_pitch;
    s32 length;
    struct SNDWaveParam wave;
    union {
        const void * data;
        SNDDuty duty;
    };
    SNDExChannelCallback callback;
    void * callback_data;
    struct SNDExChannel * nextLink;
} SNDExChannel;

typedef struct SNDWaveArc {
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;
    struct SNDWaveArcLink * topLink;
    u32 reserved[7];
    u32 waveCount;
    u32 waveOffset[0];
} SNDWaveArc;

typedef struct SNDBankData {
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;
    struct SNDWaveArcLink waveArcLink[4 ];
    u32 instCount;
    u32 instOffset[0];
} SNDBankData;

#define SND_ALARM_NUM 8

typedef enum SNDCommandID {
    SND_COMMAND_START_SEQ,
    SND_COMMAND_STOP_SEQ,
    SND_COMMAND_PREPARE_SEQ,
    SND_COMMAND_START_PREPARED_SEQ,
    SND_COMMAND_PAUSE_SEQ,
    SND_COMMAND_SKIP_SEQ,
    SND_COMMAND_PLAYER_PARAM,
    SND_COMMAND_TRACK_PARAM,
    SND_COMMAND_MUTE_TRACK,
    SND_COMMAND_ALLOCATABLE_CHANNEL,
    SND_COMMAND_PLAYER_LOCAL_VAR,
    SND_COMMAND_PLAYER_GLOBAL_VAR,
    SND_COMMAND_START_TIMER,
    SND_COMMAND_STOP_TIMER,
    SND_COMMAND_SETUP_CHANNEL_PCM,
    SND_COMMAND_SETUP_CHANNEL_PSG,
    SND_COMMAND_SETUP_CHANNEL_NOISE,
    SND_COMMAND_SETUP_CAPTURE,
    SND_COMMAND_SETUP_ALARM,
    SND_COMMAND_CHANNEL_TIMER,
    SND_COMMAND_CHANNEL_VOLUME,
    SND_COMMAND_CHANNEL_PAN,
    SND_COMMAND_SURROUND_DECAY,
    SND_COMMAND_MASTER_VOLUME,
    SND_COMMAND_MASTER_PAN,
    SND_COMMAND_OUTPUT_SELECTOR,
    SND_COMMAND_LOCK_CHANNEL,
    SND_COMMAND_UNLOCK_CHANNEL,
    SND_COMMAND_STOP_UNLOCKED_CHANNEL,
    SND_COMMAND_SHARED_WORK,
    SND_COMMAND_INVALIDATE_SEQ,
    SND_COMMAND_INVALIDATE_BANK,
    SND_COMMAND_INVALIDATE_WAVE,
    SND_COMMAND_READ_DRIVER_INFO
} SNDCommandID;

#define SND_DEFAULT_VARIABLE -1

#define SND_PLAYER_NUM 16

typedef enum {
    SND_CHANNEL_DATASHIFT_NONE,
    SND_CHANNEL_DATASHIFT_1BIT,
    SND_CHANNEL_DATASHIFT_2BIT,
    SND_CHANNEL_DATASHIFT_4BIT
} SNDChannelDataShift;

typedef enum {
    SND_WAVE_FORMAT_PCM8,
    SND_WAVE_FORMAT_PCM16,
    SND_WAVE_FORMAT_ADPCM,
    SND_WAVE_FORMAT_PSG,
    SND_WAVE_FORMAT_NOISE = SND_WAVE_FORMAT_PSG
} SNDWaveFormat;

typedef enum {
    SND_CHANNEL_LOOP_MANUAL,
    SND_CHANNEL_LOOP_REPEAT,
    SND_CHANNEL_LOOP_1SHOT
} SNDChannelLoop;

typedef enum SNDChannelOut {
    SND_CHANNEL_OUT_MIXER,
    SND_CHANNEL_OUT_BYPASS
} SNDChannelOut;

typedef enum SNDOutput {
    SND_OUTPUT_MIXER,
    SND_OUTPUT_CHANNEL1,
    SND_OUTPUT_CHANNEL3,
    SND_OUTPUT_CHANNEL1_3
} SNDOutput;

typedef struct SNDWaveData {
    struct SNDWaveParam param;
    u8 samples[0];
} SNDWaveData;

#endif
