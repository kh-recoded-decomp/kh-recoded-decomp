#include "nitro/types.h"

typedef struct {
    u8 pad[0x7d];
    u8 type;
} Entry;

extern int func_ov001_0207f018(void);
extern Entry *func_ov001_0207f028(int index);
extern int func_ov001_020827d4(Entry *entry, int arg0, int arg1);

int ForwardToFirstType11Entry_0208279c(int arg0, int arg1) {
    int i;
    int count = func_ov001_0207f018();
    for (i = 0; i < count; i++) {
        Entry *entry = func_ov001_0207f028(i);
        if (entry->type == 11) {
            return func_ov001_020827d4(entry, arg0, arg1);
        }
    }
    return 0;
}
