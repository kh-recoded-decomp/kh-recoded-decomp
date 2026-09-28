/* Loading overlay 60 installs this creation callback in the shared factory
 * slot. The object's particular in-game role is still unknown. */
typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_020d362c(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov054_020d21e0(void)
{
    SetOverlayObjectFactory(CreateOverlay060Object_020d362c);
}
