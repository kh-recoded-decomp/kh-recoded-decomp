extern int data_02063a04;

void World_SetField4_02063668(int arg0) {
    int p = *(int *)&data_02063a04;
    if (p != 0) {
        *(int *)(p + 4) = arg0;
    }
}
