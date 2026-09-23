/* Decrements a resource-group count and releases entries from a tagged section when it reaches zero. Evidence: Source implementation directly performs the described operations; see src/calls/func_0202552c.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/calls/func_0202552c.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
typedef struct {
    int group_tag;
    int reference_count;
    int *section_pointers[8];
} ResourceGroup;

extern void func_02019e60(void *pResData);

void ReleaseResourceGroup_0202d338(ResourceGroup *group)
{
    int section_index, entry_index;

    if (group->reference_count == 0) {
        return;
    }
    group->reference_count = group->reference_count - 1;
    if (group->reference_count == 0 && group->group_tag == 0x4850414b) {
        for (section_index = 0; section_index < 8; section_index++) {
            if (group->section_pointers[section_index] != 0) {
                entry_index = 0;
                while (entry_index < *(unsigned int *)group->section_pointers[section_index]) {
                    if (section_index == 7) {
                        func_02019e60((void *)group->section_pointers[section_index][entry_index + 1]);
                    }
                    entry_index = entry_index + 1;
                }
            }
        }
    }
}
