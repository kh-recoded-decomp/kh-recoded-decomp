extern int ScriptVm_ReadOperandInt(int argument, void *command);
extern void AwardSlotLevelProgress(int amount);

int ScriptCmd_AwardSlotLevelProgress(int argument, void *command)
{
    AwardSlotLevelProgress(ScriptVm_ReadOperandInt(argument, command));
    return 1;
}
