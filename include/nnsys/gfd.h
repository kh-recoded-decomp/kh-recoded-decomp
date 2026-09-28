/* NitroSystem graphics foundation: VRAM managers, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NNSYS_GFD_H
#define NNSYS_GFD_H

#include "nitro/types.h"

struct NNSGfdFrmPlttVramManager;
struct NNSGfdFrmTexRegionState;
struct NNSGfdFrmTexVramMnager;
struct NNSGfdFrmTexVramState;
struct NNSGfdVramTransferTask;
struct NNSGfdVramTransferTaskQueue;

#define NNS_GFD_TEXSIZE_MIN 0x10

#define NNS_GFD_TEXSIZE_MAX 0x7fff0

#define NNS_GFD_ALLOC_ERROR_TEXKEY 0

typedef u32 NNSGfdTexKey;

typedef struct NNSGfdFrmTexRegionState {
    u32 head;
    u32 tail;
    BOOL bActive;
    const BOOL bHalfSize;
    const u16 index;
    const u16 pad16_;
    const u32 baseAddress;
} NNSGfdFrmTexRegionState;

#define NNS_GFD_PLTTSIZE_MIN 8

#define NNS_GFD_PLTTSIZE_MAX 0x7fff8

#define NNS_GFD_4PLTT_MAX_ADDR 0x10000

#define NNS_GFD_ALLOC_ERROR_PLTTKEY 0

#define NNS_GFD_ALLOC_FROM_LOW 1

typedef u32 NNSGfdPlttKey;

typedef struct NNSGfdFrmPlttVramManager {
    u32 loAddr;
    u32 hiAddr;
    u32 szTotal;
} NNSGfdFrmPlttVramManager;

typedef enum NNS_GFD_DST_TYPE {
    NNS_GFD_DST_3D_TEX_VRAM = 0,
    NNS_GFD_DST_3D_TEX_PLTT,
    NNS_GFD_DST_3D_CLRIMG_COLOR,
    NNS_GFD_DST_3D_CLRIMG_DEPTH,
    NNS_GFD_DST_2D_BG0_CHAR_MAIN,
    NNS_GFD_DST_2D_BG1_CHAR_MAIN,
    NNS_GFD_DST_2D_BG2_CHAR_MAIN,
    NNS_GFD_DST_2D_BG3_CHAR_MAIN,
    NNS_GFD_DST_2D_BG0_SCR_MAIN,
    NNS_GFD_DST_2D_BG1_SCR_MAIN,
    NNS_GFD_DST_2D_BG2_SCR_MAIN,
    NNS_GFD_DST_2D_BG3_SCR_MAIN,
    NNS_GFD_DST_2D_BG2_BMP_MAIN,
    NNS_GFD_DST_2D_BG3_BMP_MAIN,
    NNS_GFD_DST_2D_OBJ_PLTT_MAIN,
    NNS_GFD_DST_2D_BG_PLTT_MAIN,
    NNS_GFD_DST_2D_OBJ_EXTPLTT_MAIN,
    NNS_GFD_DST_2D_BG_EXTPLTT_MAIN,
    NNS_GFD_DST_2D_OBJ_OAM_MAIN,
    NNS_GFD_DST_2D_OBJ_CHAR_MAIN,
    NNS_GFD_DST_2D_BG0_CHAR_SUB,
    NNS_GFD_DST_2D_BG1_CHAR_SUB,
    NNS_GFD_DST_2D_BG2_CHAR_SUB,
    NNS_GFD_DST_2D_BG3_CHAR_SUB,
    NNS_GFD_DST_2D_BG0_SCR_SUB,
    NNS_GFD_DST_2D_BG1_SCR_SUB,
    NNS_GFD_DST_2D_BG2_SCR_SUB,
    NNS_GFD_DST_2D_BG3_SCR_SUB,
    NNS_GFD_DST_2D_BG2_BMP_SUB,
    NNS_GFD_DST_2D_BG3_BMP_SUB,
    NNS_GFD_DST_2D_OBJ_PLTT_SUB,
    NNS_GFD_DST_2D_BG_PLTT_SUB,
    NNS_GFD_DST_2D_OBJ_EXTPLTT_SUB,
    NNS_GFD_DST_2D_BG_EXTPLTT_SUB,
    NNS_GFD_DST_2D_OBJ_OAM_SUB,
    NNS_GFD_DST_2D_OBJ_CHAR_SUB,
    NNS_GFD_DST_MAX
} NNS_GFD_DST_TYPE;

typedef void (*NNSGfdFrmTexVramDebugDumpCallBack)(int index, u32 startAddr, u32 endAddr, u32 blockMax, BOOL bActive, void * pUserContext);

#define NNS_GFD_TEXKEY_ADDR_SHIFT 3

typedef int (*NNSGfdFuncFreeTexVram)(NNSGfdTexKey key);

typedef int (*NNSGfdFuncFreePlttVram)(NNSGfdPlttKey plttKey);

typedef struct NNSGfdVramTransferTask {
    NNS_GFD_DST_TYPE type;
    void * pSrc;
    u32 dstAddr;
    u32 szByte;
} NNSGfdVramTransferTask;

typedef struct NNSGfdVramTransferTaskQueue {
    NNSGfdVramTransferTask * pTaskArray;
    u32 lengthOfArray;
    u16 idxFront;
    u16 idxRear;
    u16 numTasks;
    u16 pad16_;
    u32 totalSize;
} NNSGfdVramTransferTaskQueue;

#define NNS_GFD_NUM_TEX_VRAM_REGION 5

typedef struct NNSGfdFrmTexVramState {
    u32 address[10];
} NNSGfdFrmTexVramState;

typedef NNSGfdTexKey (*NNSGfdFuncAllocTexVram)(u32 szByte, BOOL is4x4comp, u32 opt);

typedef struct NNSGfdFrmTexVramMnager {
    u16 numSlot;
} NNSGfdFrmTexVramMnager;

#endif
