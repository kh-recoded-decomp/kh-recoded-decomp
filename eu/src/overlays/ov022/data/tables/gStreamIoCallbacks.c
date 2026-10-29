#include "nitro/types.h"

extern void func_ov022_020aa2fc(void);
extern void func_ov022_020a9294(void);
extern void SeekBitstreamCursor_020aa188(void); /* SeekBitstreamCursor */
extern void readStreamBytesSynchronously_020aa1d4(void); /* readStreamBytesSynchronously */
extern void beginAlignedFileReadAhead_020aa244(void); /* beginAlignedFileReadAhead */
extern void func_ov022_020aa2c0(void);
extern void CallVirt14_020aa2e8(void); /* CallVirt14 */

void (*gStreamIoCallbacks[7])(void) = {
    func_ov022_020aa2fc,
    func_ov022_020a9294,
    SeekBitstreamCursor_020aa188, /* SeekBitstreamCursor */
    readStreamBytesSynchronously_020aa1d4, /* readStreamBytesSynchronously */
    beginAlignedFileReadAhead_020aa244, /* beginAlignedFileReadAhead */
    func_ov022_020aa2c0,
    CallVirt14_020aa2e8, /* CallVirt14 */
};
