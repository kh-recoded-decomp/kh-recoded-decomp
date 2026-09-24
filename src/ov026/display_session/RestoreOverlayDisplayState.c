/* Restores secondary display layers and the shared display setting after the session ends.
 * Calls the ov027 teardown, restores brightness to +16 or -16 according to the saved flag, writes the saved layer mask to 0x04001000, and passes the saved setting to arm9:02029f28.
 * The display-state operations are established. The session's particular menu, scene or gameplay purpose and the shared display-setting meaning remain unknown.
 * Recovered from the persistent Ghidra caller chain and verified disassembly. */
typedef struct OverlayDisplaySession {
    unsigned char sharedState[0x647c];
    int alternateUpdate;
    int firstUpdatePending;
    int restorePositiveBrightness;
    unsigned int savedDisplayLayers;
    int savedBrightness;
    int savedDisplaySetting;
    int updateInProgress;
    void *updateRegistration;
} OverlayDisplaySession;
extern void func_ov027_020b8c58(OverlayDisplaySession *session);
extern void func_020049d0(void);
extern void SetSecondaryBrightness(int brightness);
extern void SetDisplaySetting(int setting);
void RestoreOverlayDisplayState(OverlayDisplaySession *session) {
    int brightness = -16;
    func_ov027_020b8c58(session);
    if (session->restorePositiveBrightness) brightness = 16;
    func_020049d0();
    SetSecondaryBrightness(brightness);
    *(volatile unsigned int *)0x04001000 = (*(volatile unsigned int *)0x04001000 & ~0x1f00) | (session->savedDisplayLayers << 8);
    SetDisplaySetting(session->savedDisplaySetting);
}
