extern int ScriptVm_ResolveOperand(void *p, void *cmd);
extern int ScriptVm_ReadOperandInt(void *p, int x);
extern void dispatchToHandlerAtOffset(int);

int ScriptCmd_DispatchToHandler_0208e754(void *arg0, void *cmd) {
    int r = ScriptVm_ResolveOperand(arg0, cmd);
    dispatchToHandlerAtOffset(ScriptVm_ReadOperandInt(arg0, r));
    return 1;
}
