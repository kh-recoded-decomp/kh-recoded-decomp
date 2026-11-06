# Stage actor-controller release states

Two existing ARM callbacks in overlay 001 are named from their registered state and actual manager cleanup path.

| EU identity | Table state | Proposed name | Current source |
| --- | --- | --- | --- |
| `ov001:02097d7c` | 4 | `ActorController_AwaitReleaseKeepState` | `eu/src/overlays/ov001/auto/ActorController_AwaitReleaseKeepState.c` |
| `ov001:02097d84` | 1 | `ActorController_ReleasedActorKeepState` | `eu/src/overlays/ov001/auto/ActorController_ReleasedActorKeepState.c` |

## Owner and dispatch contract

`GetStageController` resolves the pool at `gStageManager +0x18d88`. `CreateStageManager` creates that pool over the 64 records at manager +0x13d14 with stride 0x1c and lifecycle callback `HandleCommandKind1`. `GetSmallRecordIndex` computes the same backing-array index with divisor 0x1c. This is the controller owner; similarly named manager slot arrays with different offsets and strides are separate.

The native handler table is at 0x020a0318: `[NULL, state1, ControllerStateActive, ControllerRunnerDone, state4]`. The state-1 and state-4 pointer words are even ARM addresses. Both eight-byte callback bodies are `MOV R0,#0; BX LR` (`00 00 a0 e3 1e ff 2f e1`).

`UpdateActorController_02098124` reads `pending = controller +4` before invoking a handler. If pending is nonzero and differs from current +0, it copies pending to current and clears pending. It then calls `selectedHandler(controller)`. Only a nonzero result replaces pending. A zero result requests no additional transition; it does not clear a pending word that already equals the current state. These callbacks return a state-transition sentinel, not an owner pointer or a generic success BOOL.

`InitStageSpawnRequest` zero-fills the record, writes current 0 and pending 2, and marks the record active. Thus the first ordinary dispatch selects state 2, not state 1.

## State 4: waiting for manager release

`ControllerStateActive` returns 4 if the controlled actor status word at +0x26c has bit 0 set. `ControllerRunnerDone` also returns 4 when the track-slot-8 result equals 4. The dispatcher separately writes both current and pending to 4 when it sees that same actor status bit. No death, mission, boss, HP or other gameplay meaning is assigned to the bit.

`UpdateStageManager` iterates this same pool, resolves an associated actor, and calls `IsCommandType4(controller)`. A true result selects `ReleaseStageSlotEntry(4, GetSmallRecordIndex(controller))`. This makes `ActorController_AwaitReleaseKeepState` a narrow description of the registered state-4 callback. It remains quiescent until manager cleanup runs. The controller dispatcher can still execute its common timer and transform work after the callback; the name does not claim that all actor updates have stopped or that resources are already freed.

Key native instructions:

- 0x02098148–0x02098158 select the current callback and store its result to pending only if nonzero.
- 0x0209819c–0x020981a0 write current and pending 4 after the status-bit test.
- 0x02098100–0x02098106 return 4 for the track-slot-8 result.
- 0x0209bdb8 invokes `IsCommandType4`; its true branch at 0x0209bdbe reaches 0x0209be62–0x0209be6c, which computes the handle and releases it from pool 4.

## State 1: the associated actor has been released

`ReleaseSlotActor` establishes state 1 directly. For a nonzero actor ID, it releases that actor from pool 3, clears controller actorId +0xc, clears active bit 0 at +8, and writes current +0 = 1. It does not write pending +4.

`HandlePool_ReleaseHandle` invokes the configured callback with `(event = 1, element)` before returning its handle node to the free list. The controller pool callback `HandleCommandKind1` forwards event 1 to `ReleaseSlotActor`. `ShutdownStageManager` also applies that helper to the same backing array. The source and native chain therefore establish the released-actor role even though there is no demonstrated writer of pending = 1.

`ActorController_ReleasedActorKeepState` describes the state-1 return contract. It does not promise a future frame invocation after pool release, completed pool deallocation, or an initially idle actor. If a differing nonzero pending state remains, the dispatcher consumes that before selecting a callback.

Key native instructions:

- 0x020997f8–0x020997fc create the controller pool with stride 0x1c, count 0x40 and callback literal 0x020998f5; 0x02099804 stores the pool at manager +0x18d88.
- 0x0208f1e4 sets event 1; 0x0208f1f0–0x0208f1fa obtain the element and invoke the pool callback.
- 0x020998f6 checks event 1; 0x020998fc calls `ReleaseSlotActor`.
- 0x0209839e releases the actor from pool 3; 0x020983a4 clears actorId; 0x020983ae clears the active bit; 0x020983b0 writes current state 1. No instruction in that helper stores pending +4.

## Source evidence

- `eu/src/overlays/ov001/data/tables/gActorControllerStateHandlers.c:8`: `ActorControllerStateHandler gActorControllerStateHandlers`.
- `src/ov001/shared_engine/UpdateActorController_020980fc.c:70`: the state-handler table invocation.
- `src/ov001/shared_engine/GetStageController_0209c120.c:7`: `controllerTable`.
- `src/ov001/shared_engine/CreateStageManager_02099628.c:163`: `manager->pools[2] =`.
- `src/ov001/shared_engine/GetSmallRecordIndex_0209c248.c:13`: `0x1c`.
- `src/ov001/shared_engine/ControllerStateActive_02098028.c:58`: `return 4`.
- `src/ov001/shared_engine/ControllerRunnerDone_020980b4.c:36`: `return 4`.
- `src/ov001/shared_engine/UpdateActorController_020980fc.c:87`: `controller->state = 4`.
- `eu/src/overlays/ov001/calls/UpdateStageManager.c:322`: `release = IsCommandType4(command)`.
- `eu/src/overlays/ov001/calls/UpdateStageManager.c:350`: `ReleaseStageSlotEntry(4, GetSmallRecordIndex(command))`.
- `src/ov001/shared_engine/ReleaseSlotActor_02098360.c:24`: `slot->state = 1`.
- `src/ov001/shared_engine/ReleaseSlotActor_02098360.c:22`: `slot->actorId = 0`.
- `src/ov001/shared_engine/HandleCommandKind1_020998cc.c:7`: `if (kind == 1)`.
- `src/ov001/unclassified_helpers/HandlePool_ReleaseHandle_0208f1a8.c:29`: `pool->callback(1,`.
- `src/ov001/shared_engine/InitStageSpawnRequest_020982ac.c:55`: `request->kind = 2`.
- `src/ov001/shared_engine/ShutdownStageManager_0209b650.c:122`: `ReleaseSlotActor_02098360(&g_stageManager_020a0508->slots[i])`.

## Prototype and matching limits

Keep both existing four-u32 synthetic source declarations for this identity-only integration. The native bodies read no input registers, while the actual handler invoker passes a controller pointer. Four logical inputs are not inferred from those synthetic definitions, and no new parameter is introduced. The ARM mode, explicit zero result, distinct registered symbols and eight native bytes must remain unchanged.

The native review checks complete function extents, table words, owner literals and the absence of a pending-state store in ReleaseSlotActor. Official integration results follow below.


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/auto/ActorController_AwaitReleaseKeepState.c ActorController_AwaitReleaseKeepState
python tools/verify_idx.py src/overlays/ov001/auto/ActorController_ReleasedActorKeepState.c ActorController_ReleasedActorKeepState
bash tools/gate.sh
```
