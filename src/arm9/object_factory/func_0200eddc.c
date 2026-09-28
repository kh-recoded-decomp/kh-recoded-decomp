/* Loading overlay 60 installs this creation callback in the shared factory
 * slot. The object's particular in-game role is still unknown. */
typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_02057c38(void);
extern void SetOverlayObjectFactory_020031a8(OverlayObjectFactory factory);
void func_0200eddc(void)
{
    SetOverlayObjectFactory_020031a8(CreateOverlay060Object_02057c38);
}
