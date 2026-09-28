extern int Session_IsSceneInterruptible(void);
extern int Ov006_ShouldEnterConfirmState(void);

int CanAdvancePastIntro_02063cac(void) {
    if (Session_IsSceneInterruptible() != 0) {
        return 1;
    }
    return Ov006_ShouldEnterConfirmState() != 0;
}
