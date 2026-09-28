#include "nitro/types.h"

extern void func_0202eaf4(void *tables);
extern void func_0202ca18(void);
extern void func_0202c8a8(void *resource);
extern void detach_object_tree_node_0202ee1c(void *object);

void ReleaseResourceAndDetach_0202eee8(u8 *object) {
    func_0202eaf4(object + 0xd8);
    if (*(void **)(object + 0x74) != NULL) {
        func_0202ca18();
        func_0202c8a8(*(void **)(object + 0x74));
    }
    *(void **)(object + 0x74) = NULL;
    detach_object_tree_node_0202ee1c(object);
}
