#include "nitro/types.h"

typedef struct {
    void **members;
    int count;
    void *current;
} MemberList;

int FindCurrentMemberIndex_020adac0(MemberList *list) {
    int result = -1;
    int i;

    if (list->current != NULL) {
        for (i = 0; i < list->count; i++) {
            if (list->members[i] == list->current) {
                result = i;
                break;
            }
        }
    }
    return result;
}
