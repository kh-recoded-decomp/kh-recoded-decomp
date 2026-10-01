extern int data_020b7760;
extern int ParseSlotQuantityId();

int LookupChannelEntry_020b628c(int arg0) {
    return ParseSlotQuantityId(*(int *)&data_020b7760 + 25844, arg0);
}
