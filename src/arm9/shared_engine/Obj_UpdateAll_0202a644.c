extern int  func_0202a134(int arena);
extern int  Obj_Destroy(int *obj);
extern int  data_020603c8[];

void Obj_UpdateAll_0202a644(int paused)
{
    int *obj;
    int next;

    data_020603c8[1] = data_020603c8[3];
    obj = (int *)data_020603c8[1];
    while (obj != 0) {
        switch (obj[5]) {
        case -2:
            next = obj[3];
            if (!(obj[0] & 1)) {
                next = Obj_Destroy(obj);
            }
            break;
        case -1:
            next = obj[3];
            break;
        default:
            if (paused == 0 || (obj[0] & 4)) {
                int arena = func_0202a134(obj[7]);
                int cb = ((int (*)(void))((int *)data_020603c8[1])[5])();

                func_0202a134(arena);
                if (cb != 0) {
                    ((int *)data_020603c8[1])[5] = cb;
                }
            }
            next = ((int *)data_020603c8[1])[3];
            break;
        }
        data_020603c8[1] = next;
        obj = (int *)next;
    }
    data_020603c8[1] = 0;
    if (paused == 0) {
        data_020603c8[2]++;
    }
}
