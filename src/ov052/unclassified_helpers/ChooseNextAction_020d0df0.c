#include "nitro/types.h"

typedef void (*StateCallback)(int entity, int state);
typedef void (*ScaleCallback)(int entity, int scale);

typedef struct {
    int member;
    int action;
} MenuChoice;

extern BOOL func_ov052_020d10f0(int entity);
extern int SelectMenuMember_020ad980(void *list, int index, int *action);

void ChooseNextAction_020d0df0(int entity)
{
    MenuChoice *choice = (MenuChoice *)(entity + 0x9bc);
    int action;
    if (*(u32 *)(entity + 0x234) & 4) {
        if (!func_ov052_020d10f0(entity)) {
            choice->member = SelectMenuMember_020ad980((void *)(entity + 0x1070), -1, &action);
            choice->action = action;
            return;
        }
        (*(StateCallback *)(entity + 0x10ec))(entity, 3);
        return;
    }
    if (*(int *)(entity + 0x768) != 0 && *(int *)(entity + 0x75c) == 0xc && *(ScaleCallback *)(entity + 0x1fc) != NULL) {
        (*(ScaleCallback *)(entity + 0x1fc))(entity, 0xf000);
    }
    if (*(int *)(entity + 0x9c4) >= 0x1e000) {
        (*(StateCallback *)(entity + 0x10ec))(entity, 4);
    }
}
