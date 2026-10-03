#include "nitro/types.h"

extern void MovieScene_BeginDefaultFade_020647a8(void);
extern void MsgQueue_GetHeap_02064844(void);
extern void ResyncMovieSubtitleStream_02064818(void);
extern void func_ov003_02064764(void);
extern void func_ov003_020647b8(void);
extern void func_ov003_020647f0(void);
extern void thumbStep_02064850(void);

void (*data_ov003_02065880[10])(void) = {
    MovieScene_BeginDefaultFade_020647a8,
    NULL,
    ResyncMovieSubtitleStream_02064818,
    NULL,
    func_ov003_02064764,
    NULL,
    func_ov003_020647b8,
    func_ov003_020647f0,
    MsgQueue_GetHeap_02064844,
    thumbStep_02064850,
};
