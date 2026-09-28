/* Loading overlay 60 installs this creation callback in the shared factory
 * slot. The object's particular in-game role is still unknown. */
typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_02057c38(void);
extern void SetOverlayObjectFactory_02003158(OverlayObjectFactory factory);
void func_0200edc8(void)
{
    SetOverlayObjectFactory_02003158(CreateOverlay060Object_02057c38);
}
