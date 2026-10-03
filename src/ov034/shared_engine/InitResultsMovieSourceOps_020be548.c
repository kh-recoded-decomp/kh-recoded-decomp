#include "nitro/types.h"

typedef struct MovieSourceOps {
    void *open;
    void *op1;
    void *op2;
    void *op3;
    void *isOpen;
    void *close;
    void *op6;
    void *op7;
    void *op8;
} MovieSourceOps;

extern void MobiClip_SrcOpen_020bddf0(void);
extern void IsResultsInputEnabled_020bde08(void);
extern void ClearResultsFlagTwo_020bde24(void);
extern void MarkResultsComplete_020bde3c(void);
extern void MobiClip_SrcIsOpen_020bde50(void);
extern void MobiClip_SrcClose_020bde6c(void);
extern void FSi_CloseFileCommand_020bde84(void);

void InitResultsMovieSourceOps_020be548(MovieSourceOps *ops)
{
    ops->open = MobiClip_SrcOpen_020bddf0;
    ops->op1 = IsResultsInputEnabled_020bde08;
    ops->op2 = ClearResultsFlagTwo_020bde24;
    ops->op3 = MarkResultsComplete_020bde3c;
    ops->isOpen = MobiClip_SrcIsOpen_020bde50;
    ops->close = MobiClip_SrcClose_020bde6c;
    ops->op6 = NULL;
    ops->op7 = FSi_CloseFileCommand_020bde84;
    ops->op8 = NULL;
}
