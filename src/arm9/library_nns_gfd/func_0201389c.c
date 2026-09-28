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

typedef u32 NNSGfdTexKey;
typedef NNSGfdTexKey (*NNSGfdFuncAllocTexVram)(u32 szByte, BOOL is4x4comp, u32 opt);
typedef int (*NNSGfdFuncFreeTexVram)(NNSGfdTexKey key);
extern NNSGfdFuncAllocTexVram data_02055c4c;
extern NNSGfdFuncFreeTexVram data_02055c50;
void func_020137b0(int idx1st, int idx2nd, int idx3rd, int idx4th, int idx5th);
NNSGfdTexKey func_0201399c(u32 szByte, BOOL is4x4comp, u32 opt);
int func_02013b04(NNSGfdTexKey memKey);
void func_0201391c(void);
typedef struct NNSGfdFrmTexVramMnager {
    u16 numSlot;
} NNSGfdFrmTexVramMnager;
extern NNSGfdFrmTexVramMnager data_0205a8c0;
extern void func_020137b0 (int idx1st, int idx2nd, int idx3rd, int idx4th, int idx5th);
extern void func_0201391c (void);
extern NNSGfdTexKey func_0201399c (u32 szByte, BOOL is4x4comp, u32 opt);
extern int func_02013b04 (NNSGfdTexKey texKey);

void NNS_GfdInitFrmTexVramManager_0201389c (u16 numSlot, BOOL useAsDefault)
{

    if ( numSlot <= 2 ) {
        func_020137b0(4, 3, 2, 0, 1);
    } else {
        func_020137b0(4, 3, 0, 2, 1);
    }

    data_0205a8c0.numSlot = numSlot;
    func_0201391c();

    if (useAsDefault) {
        data_02055c4c = func_0201399c;
        data_02055c50 = func_02013b04;
    }
}
