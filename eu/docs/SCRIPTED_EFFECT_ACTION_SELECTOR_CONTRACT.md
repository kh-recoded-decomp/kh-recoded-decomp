# Scripted effect action-handler selection

The native consumer proves this selector returns an action-handler code
pointer paired with an output actor-state word. Existing matched prototypes
and layouts are preserved; their word-sized views are explained below.

The member selector's return was previously held as an ambiguous integer/error result. The actor entry-state consumer proves it is an action-handler code pointer, paired with an output actor-state word. This callback belongs to the ScriptedTask +0x38 action-selection interface; private onResume/errorCode labels must not become portable API names.

The declarations below reproduce the native source view after only the proposed name substitution. Generated word arguments, old private parameter labels and native pointer-width assumptions remain visible; the proven caller/writer contract is stated separately. Links use the current source paths; line labels refer to the reviewed source snapshot.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov021:020add98` | THUMB | `func_ov021_020add98` | `SelectScriptedEffectActionHandler` | [eu/src/overlays/ov021/calls/SelectScriptedEffectActionHandler.c](../src/overlays/ov021/calls/SelectScriptedEffectActionHandler.c) |

## SelectScriptedEffectActionHandler

Identity: `ov021:020add98`, THUMB, native extent 84 bytes. EU source: [eu/src/overlays/ov021/calls/SelectScriptedEffectActionHandler.c](../src/overlays/ov021/calls/SelectScriptedEffectActionHandler.c).

```c
s32 SelectScriptedEffectActionHandler(int self, s32 *event, u32 *errorCode);
```

- Owner: Member-list owner plus the selected ScriptedTask. Factory callback +0x38 selects an actor action handler; task +0x3c supplies its normal handler.
- Inputs: Member-list owner (self), selected task (legacy event label) and output actor-state word (legacy errorCode label).
- Result and effects: Native s32 holds an actor state-handler pointer. A fall-handler selection can replace it; otherwise the task's handler word at +0x3c is returned. Output state defaults to 0x16, becomes 0x18 for task category 4, or is set by the fall selector.
- Lifetime: Returns borrowed code addresses and mutates existing actor/task state; no allocation or ownership transfer.

Evidence:

- The exact body clears actor +0xa51, sets an output state word, optionally selects a fall handler, refreshes lock for IDs 0x88/0x8d, performs the motion-group operation and returns task +0x3c as fallback. Source: [eu/src/overlays/ov021/calls/SelectScriptedEffectActionHandler.c:8-27](../src/overlays/ov021/calls/SelectScriptedEffectActionHandler.c).
- EU factory binds shared add78 to the exact EU add98 callback. Source: [eu/src/overlays/ov021/calls/CreateScriptedEffectTask.c:1-20](../src/overlays/ov021/calls/CreateScriptedEffectTask.c).
- Despite private onResume/onEvent labels, the two native callback fields occupy +0x38/+0x3c. Source: [src/ov021/object_state/CreateScriptedEffectTask_020ad154.c:18-31](../../src/ov021/object_state/CreateScriptedEffectTask_020ad154.c).
- Factory registers this callback in +0x38 and an action handler in +0x3c; descriptor-specific branches can replace those fields. Source: [src/ov021/object_state/CreateScriptedEffectTask_020ad154.c:115-123](../../src/ov021/object_state/CreateScriptedEffectTask_020ad154.c).
- Member dispatch calls selectedMember.handler(list, member, command) and propagates its return; command contains the output action/state word. Source: [src/ov021/object_state/SelectMenuMember_020ad980.c:98-108](../../src/ov021/object_state/SelectMenuMember_020ad980.c).
- The actor entry state consumes SelectMenuMember's return as a StateHandler, uses a NULL fallback and stores it directly in ctl->handler. The associated output word selects actor state behavior. Source: [src/ov052/actor_motion/EnterActorState_020cd338.c:498-515](../../src/ov052/actor_motion/EnterActorState_020cd338.c).
- Fall selection returns a StateHandler pointer and writes the next-state output. This disproves the old integer-error-code interpretation. Source: [src/ov052/actor_motion/SelectFallStateHandler_020d1238.c:30-56](../../src/ov052/actor_motion/SelectFallStateHandler_020d1238.c).

Contract limits:

- Native source s32/errorCode names are retained for matching, but their actual roles are code pointer and output actor state. A portable signature must use the target platform's function-pointer type.
- No narrative names are assigned to task IDs 0x88/0x8d, task +0x68 condition, or output states 0x16/0x18.
- This is the member action-selector contract at +0x38, separate from ScriptTask update +0x24, draw +0x28 and stop notification +0x30.


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/calls/SelectScriptedEffectActionHandler.c SelectScriptedEffectActionHandler --thumb
bash tools/gate.sh
```
