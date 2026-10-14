#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ManagedActorTrigger ManagedActorTrigger;
typedef unsigned int (*ActorCondition)(ManagedActorTrigger *trigger, VecFx32 *position);

struct ManagedActorTrigger {
    u8 reserved00[0x10];
    s8 conditionMatched;
    u8 reserved11;
    s8 areaId;
    u8 reserved13;
    ActorCondition condition;
};

extern unsigned int func_ov001_02067ed4(void);
extern unsigned int func_ov001_0206dc38(void);
extern VecFx32 *GetManagedActorPosition(int index);
extern unsigned int UpdateEventTriggerDelay(ManagedActorTrigger *trigger);

int EvaluateManagedActorTrigger(ManagedActorTrigger *trigger)
{
    int result;
    VecFx32 *position;

    trigger->conditionMatched = 0;
    result = func_ov001_02067ed4();
    if (trigger->areaId != result) return 0;
    result = func_ov001_0206dc38();
    if (result <= 0) return 0;
    position = GetManagedActorPosition(0);
    result = trigger->condition(trigger, position);
    if (result != 0) {
        trigger->conditionMatched = 1;
        result = UpdateEventTriggerDelay(trigger);
        if (result == 0) return 0;
    }
    return (int)trigger->conditionMatched;
}
