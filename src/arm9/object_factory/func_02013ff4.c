/* Loading overlay 60 installs this creation callback in the shared factory
 * slot. The object's particular in-game role is still unknown. */
typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_0205a8d0(void);
extern void SetOverlayObjectFactory_02013f20(OverlayObjectFactory factory);
void func_02013ff4(void)
{
    SetOverlayObjectFactory_02013f20(CreateOverlay060Object_0205a8d0);
}
