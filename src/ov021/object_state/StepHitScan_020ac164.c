#include "nitro/types.h"

typedef struct {
    u32 data[0x35];
} HitResult;

typedef struct {
    HitResult result;
    int state;
    void *pending;
} HitScan;

typedef struct {
    u8 pad_00[0x24];
    u16 flagsLow : 10;
    u16 skipContacts : 1;
    u16 flag11 : 1;
    u16 skipNearest : 1;
    u16 flagsHigh : 3;
} HitOptions;

extern BOOL IsFirstEntryFlagSet_0206e584(void);
extern void func_ov021_020ac148(HitScan *scan);
extern void *func_ov001_0207f08c(void);
extern void *func_ov001_0208723c(void);
extern void func_ov001_02087884(void);
extern BOOL func_ov021_020ab930(int type, void *attack, HitOptions *options, HitScan *scan);
extern BOOL ResolveNearestHitNode_020aba18(int type, void *attack, HitOptions *options, HitScan *scan);
extern BOOL ResolveHitContacts_020abc40(int type, void *attack, HitOptions *options, HitScan *scan);
extern void func_ov021_020abe54(int type, void *attack, HitOptions *options, HitScan *scan);

BOOL StepHitScan_020ac164(int type, void *attack, HitOptions *options, HitScan *scan) {
    BOOL proceed;
    if (IsFirstEntryFlagSet_0206e584()) {
        return FALSE;
    }
    if (scan->state >= 8) {
        return FALSE;
    }
    func_ov021_020ac148(scan);
    switch (scan->state) {
    case 1:
        scan->pending = func_ov001_0207f08c();
        scan->state = 2;
    case 2:
        if (func_ov021_020ab930(type, attack, options, scan)) {
            proceed = TRUE;
            if (options != NULL && options->skipNearest) {
                proceed = FALSE;
            }
            if (proceed) {
                scan->state = 3;
            } else {
                scan->state = 5;
            }
        }
        break;
    case 3:
        scan->pending = func_ov001_0208723c();
        scan->state = 4;
    case 4:
        if (ResolveNearestHitNode_020aba18(type, attack, options, scan)) {
            scan->state = 5;
        }
        break;
    case 5:
        func_ov001_02087884();
        scan->state = 6;
    case 6:
        if (ResolveHitContacts_020abc40(type, attack, options, scan)) {
            proceed = TRUE;
            if (options != NULL && options->skipContacts) {
                proceed = FALSE;
            }
            if (proceed) {
                scan->state = 7;
            } else {
                scan->state = 8;
            }
        }
        break;
    case 7:
        func_ov021_020abe54(type, attack, options, scan);
        scan->state = 8;
        break;
    }
    return TRUE;
}
