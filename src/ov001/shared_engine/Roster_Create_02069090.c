extern int InstantiateClass();
extern int Ov002_Roster_Reset();
extern int data_0209eacc;
extern int data_0209eac8;

void Roster_Create_02069090(void) {
    data_0209eac8 = InstantiateClass(&data_0209eacc, 0);
    Ov002_Roster_Reset();
}
