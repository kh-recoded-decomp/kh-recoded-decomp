/* Loading overlay 60 installs this creation callback in the shared factory
 * slot. The object's particular in-game role is still unknown. */
typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_02013b94(void);
extern void SetOverlayObjectFactory_02013bac(OverlayObjectFactory factory);
void func_02013b98(void)
{
    SetOverlayObjectFactory_02013bac(CreateOverlay060Object_02013b94);
}
