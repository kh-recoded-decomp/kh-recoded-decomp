#ifndef EU_SLOT_HELP_PROMPT_H
#define EU_SLOT_HELP_PROMPT_H

#include "nitro/types.h"

typedef struct SlotHelpPromptDefinition SlotHelpPromptDefinition;
struct SlotHelpPromptDefinition {
    u8 flagIndex;
    u8 messageIndex;
    s8 align;
    u8 unknown03;
    u16 unknown04;
    u16 unknown06;
    void (*onOpen)(void *, const SlotHelpPromptDefinition *);
};

extern const SlotHelpPromptDefinition gEquipmentSlot0HelpPrompt;
extern const SlotHelpPromptDefinition gEquipmentSlot1HelpPrompt;
extern SlotHelpPromptDefinition gEquipmentOtherSlotHelpPrompt;

typedef char SlotHelpPromptIs12Bytes[sizeof(SlotHelpPromptDefinition) == 12 ? 1 : -1];
typedef char SlotHelpPromptAlignOffset[
    (u32)&((SlotHelpPromptDefinition *)0)->align == 2 ? 1 : -1];
typedef char SlotHelpPromptField06Offset[
    (u32)&((SlotHelpPromptDefinition *)0)->unknown06 == 6 ? 1 : -1];
typedef char SlotHelpPromptCallbackOffset[
    (u32)&((SlotHelpPromptDefinition *)0)->onOpen == 8 ? 1 : -1];

#endif
