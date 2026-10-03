#include "nitro/types.h"

extern void CallVirt14_020aa2c8(void);
extern void SeekBitstreamCursor_020aa168(void);
extern void beginAlignedFileReadAhead_020aa224(void);
extern void func_ov022_020a9274(void);
extern void func_ov022_020aa2a0(void);
extern void func_ov022_020aa2dc(void);
extern void readStreamBytesSynchronously_020aa1b4(void);

void (*data_ov022_020b7d4c[7])(void) = {
    func_ov022_020aa2dc,
    func_ov022_020a9274,
    SeekBitstreamCursor_020aa168,
    readStreamBytesSynchronously_020aa1b4,
    beginAlignedFileReadAhead_020aa224,
    func_ov022_020aa2a0,
    CallVirt14_020aa2c8,
};
