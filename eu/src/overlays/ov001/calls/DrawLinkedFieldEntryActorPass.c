#include "nitro/types.h"

extern void SceneNode_Draw(int arg);
extern int QueryLinkTarget(void);
extern int GetFieldEntryDrawBlockMask(void);

typedef void (*Callback)(int);

void DrawLinkedFieldEntryActorPass(int param1, int useCallback) {
    int obj = QueryLinkTarget();
    if (useCallback == 0 && GetFieldEntryDrawBlockMask() == 0) {
        Callback cb = *(Callback *)(*(int *)(obj + 4) + 0x38);
        if (cb != 0) {
            cb(obj);
            return;
        }
        SceneNode_Draw(param1 + 0x14);
    }
}
