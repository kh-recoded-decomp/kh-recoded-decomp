/* Applies up to two indexed values from the selected value set, skipping minus-one entries, and records which set was used.
 * BK9E normal values are at +0x54, alternate values at +0x44, and the selection bit is at +0x94 with inverted boolean storage.
 * Adapted CC0 C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, src/overlays/ov025/calls/func_ov025_020887c0.c. */

extern void func_0204f24c(int target, int index, unsigned int value);

struct Ov008SubitemBlock { char pad0[0x14]; int idx[2]; char pad1[0x28]; unsigned int alt[2]; char pad2[8]; unsigned int val[2]; char pad3[0x94-0x5c]; unsigned int bUseAlt:1; };

void ApplySelectedSubitemValues_020b94fc(int target, struct Ov008SubitemBlock *obj, int useAlt) {
    int i = 0;
    do {
        int index = obj->idx[i];
        if (index != -1) {
            if (useAlt != 0) {
                unsigned int v = obj->alt[i];
                if (v != 0xffffffff) func_0204f24c(target, index, v);
            } else {
                unsigned int v = obj->val[i];
                if (v != 0xffffffff) func_0204f24c(target, index, v);
            }
        }
        i++;
    } while (i < 2);
    obj->bUseAlt = (useAlt == 0);
}
