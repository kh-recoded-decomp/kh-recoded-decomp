extern void Cmd_DispatchWithFlag();
extern void Gfx_DispatchByPairKeyA();
extern void Gfx_DispatchByPairKeyB();
extern void DispatchThreeOptionalOpsB();
void DispatchByPartType_0202b4c0(int param_1, unsigned short *param_2, int param_3, int *param_4, int param_5, int param_6)
{
    switch (param_2[3]) {
    case 0:
        Cmd_DispatchWithFlag(param_1, param_2, param_5, param_6);
        break;
    case 1:
        Gfx_DispatchByPairKeyA(param_1, param_2, param_5, param_6);
        break;
    case 2:
        Gfx_DispatchByPairKeyB(param_1, param_2, param_5, param_6);
        break;
    }
    DispatchThreeOptionalOpsB(param_1, (int)param_2, param_3, param_4);
}
