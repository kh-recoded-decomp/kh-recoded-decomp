/* Calls the shared current-context getter and returns zero to the session caller.
 * The complete function calls arm9:0202a764 then returns 0; BeginOverlayDisplaySession returns this callback address.
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
extern OverlayDisplaySession *func_020b9fac(void);
int func_ov027_020ba104(void) { func_020b9fac(); return 0; }
