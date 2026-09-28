/* Tests a downward vector from an object position; writes the scaled hit position when a result exists, otherwise copies the original position.
 * Target result scalar is at offset 0x2c, established by LDR and the scale/add helper call; specific collision surface is unknown.
 * Adapted CC0 C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, src/calls/func_0202b0b8.c. */
typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Entry {
    char pad_0000[8];
    VecFx32 pos;
} Entry;

typedef struct Hit {
    char pad_0000[0x2c];
    int distance2c;
} Hit;

extern Entry *func_020352cc(void *cont);
extern Hit *func_01ffceb4(void *world, VecFx32 *from, VecFx32 *dir);
extern void func_020301ac(int s, const VecFx32 *dir, const VecFx32 *from, VecFx32 *out);

int ProjectPositionDownward_020352e0(void *cont, int p3, void *out) {
    Entry *entry = func_020352cc(cont);
    VecFx32 from;
    VecFx32 dir;
    Hit *hit;

    from.x = entry->pos.x;
    from.y = entry->pos.y + 0x1000;
    from.z = entry->pos.z;
    dir.x = 0;
    dir.y = -0x5000;
    dir.z = 0;

    hit = func_01ffceb4(cont, &from, &dir);
    if (hit != 0) {
        func_020301ac(hit->distance2c, &dir, &from, (VecFx32 *)out);
        return 1;
    }
    *(VecFx32 *)out = entry->pos;
    return 0;
}
