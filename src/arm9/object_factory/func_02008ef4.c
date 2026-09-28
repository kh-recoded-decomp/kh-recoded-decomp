/* Loading overlay 60 installs this creation callback in the shared factory
 * slot. The object's particular in-game role is still unknown. */
typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object_02056f48(void);
extern void SetOverlayObjectFactory_02008d9c(OverlayObjectFactory factory);
void func_02008ef4(void)
{
    SetOverlayObjectFactory_02008d9c(CreateOverlay060Object_02056f48);
}
