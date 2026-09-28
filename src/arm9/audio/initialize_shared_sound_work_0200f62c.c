extern void DC_FlushRange(void *address, unsigned int size);

typedef struct SndSharedWorkSlot {
    short cells[16];
    int val;
} SndSharedWorkSlot;

typedef struct SndSharedWork {
    int field_00;
    int field_04;
    short field_08;
    short field_0a;
    unsigned char pad_0c[0x20 - 0x0c];
    SndSharedWorkSlot slots[16];
    short field_260[16];
} SndSharedWork;

void initialize_shared_sound_work_0200f62c(SndSharedWork *sharedWork) {
    int slotIndex;
    int cellIndex;

    sharedWork->field_04 = 0;
    sharedWork->field_08 = 0;
    sharedWork->field_0a = 0;
    sharedWork->field_00 = 0;

    for (slotIndex = 0; slotIndex < 16; slotIndex++) {
        sharedWork->slots[slotIndex].val = 0;
        for (cellIndex = 0; cellIndex < 16; cellIndex++) {
            sharedWork->slots[slotIndex].cells[cellIndex] = -1;
        }
    }

    for (cellIndex = 0; cellIndex < 16; cellIndex++) {
        sharedWork->field_260[cellIndex] = -1;
    }

    DC_FlushRange(sharedWork, 0x280);
}
