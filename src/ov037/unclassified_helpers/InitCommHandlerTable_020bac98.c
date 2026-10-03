#include "nitro/types.h"

typedef struct CommHandlerTable {
    void *open;
    void *start;
    void *poll;
    void *reserved0;
    void *isActive;
    void *release;
    void *apply;
    void *reserved1;
    void *update;
    void *close;
} CommHandlerTable;

extern void func_ov037_020bab78(void);
extern void func_ov037_020bab9c(void);
extern void func_ov037_020babc8(void);
extern void IsPxiChannelActive_020babec(void);
extern void ReleasePxiChannel_020bac10(void);
extern void ApplyCommRequest_020bac30(void);
extern void func_ov037_020baa70(void);
extern void func_ov037_020bac84(void);

void InitCommHandlerTable_020bac98(CommHandlerTable *table)
{
    table->open = func_ov037_020bab78;
    table->start = func_ov037_020bab9c;
    table->poll = func_ov037_020babc8;
    table->reserved0 = NULL;
    table->isActive = IsPxiChannelActive_020babec;
    table->release = ReleasePxiChannel_020bac10;
    table->apply = ApplyCommRequest_020bac30;
    table->reserved1 = NULL;
    table->update = func_ov037_020baa70;
    table->close = func_ov037_020bac84;
}
