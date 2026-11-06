# Field preparation after an actor scene

| EU identity | Name | Native declaration | Source |
|---|---|---|---|
| ov001:0206375c, Thumb, 220 bytes | `PrepareFieldAfterActorScene` | void(void) | src/overlays/ov001/calls/PrepareFieldAfterActorScene.c |

The actor-scene task establishes this helper's lifecycle boundary. Its initializer publishes gActorSceneManager and records the owning task handle at manager +0x3ee4. Scene startup installs its intro continuation on that task. When the actor VM and transition gates finish, RunEventScriptFrame installs TryShutdownActorSystem. That continuation waits for the field panel and transition predicates, finishes the event camera cut, restores VRAM and clears actor slots before calling PrepareFieldAfterActorScene.

After the call, TryShutdownActorSystem keeps field entries paused, frees and clears its scene handle, performs its existing state-6 event branch and returns ActorScene_IdleTaskUpdate. The task runner installs a returned nonzero continuation; the idle continuation then returns zero to remain installed. This is field preparation at the actor-scene handoff. It does not promise that field simulation, input or every subsystem has resumed.

The helper clears session +0x20 mask 0x20, deactivates manager entries, pauses field entries, forwards camera frozen=0, refreshes field objects and reconnects actor-slot bindings. It snapshots each managed actor's current position and bias-adjusted halfword through StoreSessionSpawnPoint. That writer preserves its existing session +0x27b6 bit-0 gate. No new index, pointer or owner guard is added.

ResumeTaskAndClearFlags acts on the separate gFieldEffectPool owner. When its word at +0x4c is nonzero, it passes the embedded actor-registry node at +0x3c to ActorSlot_LinkAsRoot, then clears the low two bits of byte +0x20f. EnsureFieldEffectPool initializes the same node and DestroyFieldEffectPool unlinks it. This is distinct from the Obj_UpdateAll task and does not undo SetFieldEntriesPaused(1). When flag 0x3528 is absent, the two existing conditional stage-manager flag clear helpers also run. The flag remains a numeric policy selector; its story or gameplay interpretation is not established here.

The sound branches remain distinct:

| Initial flag 0x360c | Session state | Existing operations |
|---|---|---|
| Set | 6 | Restore sound-heap level 1, clear the flag, then call QueueAreaSceneSoundState(1). |
| Set | Other | Restore level 1, clear the flag, queue area archives, update event objects, invoke the optional stage sound bridge and save sound-heap level 2. |
| Clear | 6 | Restore sound-heap level 2, then call QueueAreaSceneSoundState(0). |
| Clear | Other | Restore sound-heap level 2. |

ReleaseSeqArcHeapLevel loads a recorded state through NNS_SndHeapLoadState. CacheSeqArcStatus saves a state through NNS_SndHeapSaveState. The historical stopSeq parameter label on QueueAreaSceneSoundState does not establish a stop-sequence Boolean: its nonzero branch saves level 2. Preserve all commands, rechecks, forwarding and ordering. The optional bridge invokes QueueStageResourceSounds only while its stage owner is active; no additional callback role is inferred.

Finally, a zero cached main brightness setting clears session +0x214 mask 0x40000. This is the cached setting, not a direct display register or a completion guarantee. All numeric state values, flags and brightness behavior stay intact.

The prior EU source was src/overlays/ov001/calls/PrepareFieldAfterActorScene.c. Its historical ROOT counterpart remains src/ov001/unclassified_helpers/func_ov001_0206375c.c. The existing EU standalone body is preserved. ACTOR_SCENE_FIELD_HANDOFF1_REVIEW_V1.json records exact source paths and numbered evidence, native declarations, complete original BK9P NDS function comparisons, the direct caller BL and the original idle-continuation literal. No compiler or gate was run for this research.




## Active EU sources

- [PrepareFieldAfterActorScene](../src/overlays/ov001/calls/PrepareFieldAfterActorScene.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/PrepareFieldAfterActorScene.c PrepareFieldAfterActorScene --thumb
bash tools/gate.sh
```
