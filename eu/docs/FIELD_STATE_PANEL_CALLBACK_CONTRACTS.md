# Field-object state and panel callback contracts (ov018-020)

These 18 EU names follow actual constructor assignments, paired writers and
consumers, callback dispatch and native argument/return flow. Original EU
identities distinguish overlays sharing RAM addresses. Names and comments
preserve existing prototypes, callback presence and instruction behavior.

## Identities and evidence

The first path below is the EU compilation wrapper, relative to `eu/`. Shared source evidence uses repository-root paths and must be read through the wrapper aliases; the US address suffix is not the EU identity.

| EU identity | Proposed name | EU source | Evidence |
|---|---|---|---|
| ov018:020a1f04 (thumb) | `IsKind6ObjectType1Or10` | `src/overlays/ov018/calls/IsKind6ObjectType1Or10.c` | `eu/src/overlays/ov018/calls/RespawnKind6FieldObject.c` |
| ov018:020a2220 (arm) | `IsKind6ObjectStateNonzero` | `src/overlays/ov018/calls/IsKind6ObjectStateNonzero.c` | `src/ov018/unclassified_helpers/CreateKind6EntryPool_020a3198.c` |
| ov018:020a31b0 (thumb) | `Kind6Object_OnActorSlotRefreshNoop` | `src/overlays/ov018/auto/Kind6Object_OnActorSlotRefreshNoop.c` | `src/ov001/field_objects/FieldObject_ApplyActorSlotIndex_02086384.c` |
| ov018:020a31b4 (thumb) | `Kind6Object_OnResourceCacheShutdownNoop` | `src/overlays/ov018/auto/Kind6Object_OnResourceCacheShutdownNoop.c` | `src/ov001/unclassified_helpers/ResourceCache_Shutdown_02087190.c` |
| ov018:020a3424 (thumb) | `ResetKind6ObjectStateAndPose` | `src/overlays/ov018/calls/ResetKind6ObjectStateAndPose.c` | `eu/src/overlays/ov018/calls/ReactivateKind6FieldObject.c` |
| ov018:020a3490 (thumb) | `IsKind6ObjectState1Or2` | `src/overlays/ov018/calls/IsKind6ObjectState1Or2.c` | `src/ov018/field_objects/FieldObject_ShiftWithArea_020a29e0.c` |
| ov018:020a34a4 (thumb) | `ReactivateKind6FieldObject` | `src/overlays/ov018/calls/ReactivateKind6FieldObject.c` | `eu/src/overlays/ov018/calls/RespawnKind6FieldObject.c` |
| ov019:020a23cc (thumb) | `LinkedObject_NextLinkHitHookNoop` | `src/overlays/ov019/auto/LinkedObject_NextLinkHitHookNoop.c` | `src/ov019/unclassified_helpers/HandleLinkHit_020a2774.c` |
| ov020:020a20b0 (thumb) | `LoadKind2PanelBlockPhase` | `src/overlays/ov020/calls/LoadKind2PanelBlockPhase.c` | `src/ov020/unclassified_helpers/CreateKind2EntryPool_020a26b4.c` |
| ov020:020a21d4 (arm) | `Kind2Panel_OnSetActiveNoop` | `src/overlays/ov020/auto/Kind2Panel_OnSetActiveNoop.c` | `src/ov001/unclassified_helpers/CacheEntry_SetActive_02087258.c` |
| ov020:020a21d8 (arm) | `Kind2Panel_EntryEventTrue` | `src/overlays/ov020/auto/Kind2Panel_EntryEventTrue.c` | `src/ov020/unclassified_helpers/CreateKind2EntryPool_020a26b4.c` |
| ov020:020a2364 (arm) | `Kind2Panel_OnActorSlotRefreshNoop` | `src/overlays/ov020/auto/Kind2Panel_OnActorSlotRefreshNoop.c` | `src/ov001/field_objects/FieldObject_ApplyActorSlotIndex_02086384.c` |
| ov020:020a2850 (arm) | `GetPanelBlockFlag8000` | `src/overlays/ov020/auto/GetPanelBlockFlag8000.c` | `eu/src/overlays/ov020/calls/ActivatePanel.c` |
| ov020:020a2920 (arm) | `PanelBlock_NextLinkActivationHookNoop` | `src/overlays/ov020/auto/PanelBlock_NextLinkActivationHookNoop.c` | `eu/src/overlays/ov020/calls/ActivatePanel.c` |
| ov020:020a34a4 (arm) | `GetPanelBlockHiddenMask` | `src/overlays/ov020/auto/GetPanelBlockHiddenMask.c` | `eu/src/overlays/ov020/calls/SetBlockHidden.c` |
| ov020:020a34b0 (arm) | `GetPanelBlockFlag200` | `src/overlays/ov020/auto/GetPanelBlockFlag200.c` | `src/ov020/unclassified_helpers/SpawnStackedBlock_020a3278.c` |
| ov020:020a3598 (arm) | `Kind3Panel_OnSetActiveNoop` | `src/overlays/ov020/auto/Kind3Panel_OnSetActiveNoop.c` | `src/ov020/unclassified_helpers/CreateKind3EntryPool_020a3940.c` |
| ov020:020a359c (arm) | `Kind3Panel_EntryEventTrue` | `src/overlays/ov020/auto/Kind3Panel_EntryEventTrue.c` | `src/ov020/unclassified_helpers/CreateKind3EntryPool_020a3940.c` |

## Exact owners and layout boundaries

The common entry prefix stores its pool/ops owner at +4, a per-entry update pointer at +0x0c, flags at +0x30, actor ID at +0x32, position at +0x38 and the actor-slot animation-group/pose byte at +0x47. The pool category is at pool+0x5a. These offsets do not make the per-kind tails interchangeable.

Kind6 (`CreateKind6EntryPool`) allocates 0xbc-byte entries in a 0x474-byte header pool. Its object flags are u16 +0x50, motion-state is signed byte +0x52, velocity is +0x64, anchor is +0x94, and per-object signed32 type is +0xa0. The pool category is 6, while object types 1/2/3/10 belong to a separate field. No gameplay class label is inferred for those values.

Kind1 stacked panels (`CreatePanelEntryPool`) allocate 0x70-byte entries. Their u16 flags live at +0x54; masks 8, 0x200 and 0x8000 are independent. The factory sets 0x200 for signed linkB >= 0. The phase loader uses it to choose phase 0 or 1; activation has its own branch on the same mask. Activation sets 0x8000 and link traversal skips that bit. This proves the operations, without proving a broader destroyed/complete state.

Kind2 pools allocate 0x50-byte entries and kind3 pools allocate 0x5c-byte entries, each with a 0x60-byte header. Their callbacks share the common prefix contract, not the kind1 +0x54 tail. Kind2 phase loading uses signed scale bytes +0x49..+0x4b multiplied by 0x1800 in native fixed-point units; it only acts for phase 2.

## Callback dispatch and return values

The constructor callback array is indexed in 4-byte words. Actual readers establish the following roles; private constructor labels such as onInit/onEnter/onRelease are not independent ABI evidence.

| Pool offset | Actual reader | Native contract |
|---|---|---|
| +0x00 | resource phase dispatch | Owner-specific phase loader, including phase and u16 actor-counter arguments |
| +0x04 | `ResourceCache_Shutdown` (EU001:020871b8) | Calls hook(entry), then overwrites R0 at 020871d2 and installs the actor callback; this is not the per-frame entry update or destructor |
| +0x0c | `FieldObject_ApplyActorSlotIndex` | Calls hook(entry) after actor-slot scan when binding flag 4 is set; residual R0 can propagate |
| +0x10 / +0x14 | `DestroyEntryPool` | Per-entry / pool teardown, distinct from +0x04 |
| +0x18 | `CacheEntry_SetActive` | Common state/world-registration work precedes hook(entry,active); an empty hook does not cancel it |
| +0x1c | common entry hit/push-event dispatcher | Forwards entry/event and returns the callback result; literal 1 has no recovered accept/reject/stop label |
| +0x30 | owner-specific query | Kind6 canonical state != 0; kind1 raw flags & 0x8000; these are not the same query semantics |

The kind2 and kind3 event stubs each return literal 1. ARM BX LR activation/refresh hooks and Thumb BX LR hooks preserve the incoming R0 word. No fluent pointer, owned-pointer or BOOL API is introduced from a residual register alone. The source plan only renames identities and paths.

The ov019 next-link hook and ov020 next-panel hook are different empty functions with different caller owners. Their callers pass `(nextLiveLink,current)` after a previous-link settle helper. R0 is overwritten before use: ov019 BLX 020a28e0 then LDR R0 020a28e8; ov020 BL 020a2bd4 then LDR R0 020a2bdc. Both hooks may remain logical void for a port.

## Per-function behavior and limits

### `IsKind6ObjectType1Or10`

Compares signed32 field+A0h with1 or10 and returns canonical BOOL. The kind6 factory writes1/3 there; respawn takes an explicit type and resolves10 against the unlock-state query before this predicate gates packed-session flag changes.

Pool category6 is separate from per-object type+A0h. No gameplay class name is assigned to either numeric value.

### `IsKind6ObjectStateNonzero`

Registered pool callback12 at+30h returns whether signed byte+52h is nonzero. The factory initializes this motion-state byte0; the pushed-motion and respawn implementations read/write the same owner field.

Canonical BOOL, not raw mask. Nonzero is not named busy/disabled: state1 and2 have distinct consumers.

### `Kind6Object_OnActorSlotRefreshNoop`

Kind6 constructor installs this empty callback at pool+0Ch. The real common dispatcher invokes it with the entry after the actor-slot scan when binding flag4 is set.

BX LR preserves incoming R0 and may propagate through the common dispatcher. No new BOOL or ownership result is proposed.

### `Kind6Object_OnResourceCacheShutdownNoop`

Kind6 constructor installs this empty callback at pool+4. ResourceCache_Shutdown walks the entry list, invokes ops+4(entry), then obtains the actor slot and installs its callback before freeing cached resource slots.

This is not a per-frame update or entry destructor. Caller overwrites R0 at EU001:020871d2 immediately after BLX; the empty hook itself preserves R0.

### `ResetKind6ObjectStateAndPose`

Writes pose byte+47h and state byte+52h to0, conditionally rebinds actor animation for binding flag4, conditionally applies record table5 when slot flag2 is clear, then clears object flags50h bits10h/20h.

Does not reset position, velocity, type, links or the whole object. Native caller retains the object in R0 for this worker despite an empty-parameter legacy call declaration.

### `IsKind6ObjectState1Or2`

Returns canonical BOOL for signed state byte+52h equal to1 or2. ShiftWithArea and actor059 contact/update paths consume this exact predicate.

No idle/airborne/active gameplay interpretation is assigned. Preserve both numeric states and signed-byte read.

### `ReactivateKind6FieldObject`

Respawn helper resets state/pose, rebinds animation, enables the actor slot, conditionally transitions record slot when flag100h is clear, clears disabled state, resets kind direction and sets render flags8/10h.

This is a bounded reactivation helper, not a constructor or full respawn: caller owns positioning, active-list operation, type/unlock handling, velocity and hit-handler setup.

### `LinkedObject_NextLinkHitHookNoop`

On the hit-transition path, HandleLinkHit finds the next live link and invokes this empty hook as(next,current). The previous-live-link branch instead calls the nonempty settle-height helper.

No settling, reward or completion semantics are assigned to this empty function. After BLX at EU019:020a28e0, R0 is overwritten by a literal load at020a28e8 before use.

### `LoadKind2PanelBlockPhase`

Registered kind2 pool callback0 acts only for phase2: spawns/binds the actor from entry+38h position and signed scale bytes49h..4Bh, consumes/increments the u16 actor counter, prepares animation/collision/extra-position type7 and sets binding flag4.

No action for other phases. Scale steps use native1800h units; counter wrapping, two inactive-predicate calls and call order remain. This is not the distinct kind1 stacked-block phase loader.

### `Kind2Panel_OnSetActiveNoop`

Kind2 constructor installs empty ops+18h. Common CacheEntry_SetActive performs inactive-bit/world-registration work then invokes this hook as(entry,active).

Does not cancel common activation side effects. Native BX LR preserves incoming R0; no signature or logical result is added.

### `Kind2Panel_EntryEventTrue`

Kind2 pool installs literal1 callback at+1Ch, the actual field-entry hit/push-event dispatch slot. The hook reads no arguments and changes no memory.

Preserve literal1 without interpreting it as accept/reject/stop/handled. Common dispatcher forwards its result.

### `Kind2Panel_OnActorSlotRefreshNoop`

Kind2 constructor installs empty callback at+0Ch, called after the common actor-slot refresh scan.

Distinct from +18h activation and +1Ch event hooks. Residual R0 may propagate through the dispatcher; no ownership or BOOL claim.

### `GetPanelBlockFlag8000`

Kind1 stacked-panel constructor installs pool callback12; leaf returns u16 flags+54h masked with8000h. ActivatePanel sets this bit, while live-link scans, phase loading and visibility handling test it.

Raw return is0 or8000h, not canonical BOOL. Keep operational name: the exact lifecycle state is not broadened to destroyed/owned/complete.

### `PanelBlock_NextLinkActivationHookNoop`

After activating a kind1 panel and settling the previous live block, ActivatePanel calls this empty hook as(nextLiveBlock,currentPanel) when a next live block exists.

No propagation/settling is performed here. Native R0 is overwritten by a literal load at020a2bdc after call020a2bd4; preserve surrounding activation flags/rewards.

### `GetPanelBlockHiddenMask`

Returns u16 flags+54h masked with8. Paired SetBlockHidden sets/clears this exact bit and render flags8/10h, then combines the predicate with8000h to enable or disable actor visibility.

Returns0 or8; no canonicalization or merging with active/activated flags. Owner is the kind1 stacked panel, not kind2 or kind3 blocks.

### `GetPanelBlockFlag200`

Returns u16 flags+54h masked with200h. Factory sets this bit when signed linkB>=0; phase loader selects phase0 versus1 and ActivatePanel branches on the same bit. The map-icon updater also consumes the predicate.

Raw return0/200h. The linkB/event-phase distinction is proven; no quest/locked/reward gameplay label is inferred.

### `Kind3Panel_OnSetActiveNoop`

Kind3 pool constructor installs the empty +18h activation hook used by CacheEntry_SetActive(entry,active).

Separate owner/address from kind2 counterpart. Common activation still executes; empty body preserves R0 without creating logical return semantics.

### `Kind3Panel_EntryEventTrue`

Kind3 pool constructor installs a literal1 callback at+1Ch; the common hit/push-event dispatcher forwards its return.

No arguments read or memory effects; no numeric event-result meaning is asserted. Do not combine with kind2 duplicate.

## Reproducing the observations

Inspect the EU wrapper and any shared include together. For example:

```powershell
Get-Content eu/src/overlays/ov018/calls/FieldObject_ShiftWithArea.c
Get-Content src/ov018/field_objects/FieldObject_ShiftWithArea_020a29e0.c
Get-Content eu/src/overlays/ov020/calls/ActivatePanel.c
Get-Content src/ov001/unclassified_helpers/ResourceCache_Shutdown_02087190.c
Get-Content eu/config/arm9/overlays/ov018/symbols.txt
```


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov018/calls/IsKind6ObjectType1Or10.c IsKind6ObjectType1Or10 --thumb
python tools/verify_idx.py src/overlays/ov018/calls/IsKind6ObjectStateNonzero.c IsKind6ObjectStateNonzero
python tools/verify_idx.py src/overlays/ov018/auto/Kind6Object_OnActorSlotRefreshNoop.c Kind6Object_OnActorSlotRefreshNoop --thumb
python tools/verify_idx.py src/overlays/ov018/auto/Kind6Object_OnResourceCacheShutdownNoop.c Kind6Object_OnResourceCacheShutdownNoop --thumb
python tools/verify_idx.py src/overlays/ov018/calls/ResetKind6ObjectStateAndPose.c ResetKind6ObjectStateAndPose --thumb
python tools/verify_idx.py src/overlays/ov018/calls/IsKind6ObjectState1Or2.c IsKind6ObjectState1Or2 --thumb
python tools/verify_idx.py src/overlays/ov018/calls/ReactivateKind6FieldObject.c ReactivateKind6FieldObject --thumb
python tools/verify_idx.py src/overlays/ov019/auto/LinkedObject_NextLinkHitHookNoop.c LinkedObject_NextLinkHitHookNoop --thumb
python tools/verify_idx.py src/overlays/ov020/calls/LoadKind2PanelBlockPhase.c LoadKind2PanelBlockPhase --thumb
python tools/verify_idx.py src/overlays/ov020/auto/Kind2Panel_OnSetActiveNoop.c Kind2Panel_OnSetActiveNoop
python tools/verify_idx.py src/overlays/ov020/auto/Kind2Panel_EntryEventTrue.c Kind2Panel_EntryEventTrue
python tools/verify_idx.py src/overlays/ov020/auto/Kind2Panel_OnActorSlotRefreshNoop.c Kind2Panel_OnActorSlotRefreshNoop
python tools/verify_idx.py src/overlays/ov020/auto/GetPanelBlockFlag8000.c GetPanelBlockFlag8000
python tools/verify_idx.py src/overlays/ov020/auto/PanelBlock_NextLinkActivationHookNoop.c PanelBlock_NextLinkActivationHookNoop
python tools/verify_idx.py src/overlays/ov020/auto/GetPanelBlockHiddenMask.c GetPanelBlockHiddenMask
python tools/verify_idx.py src/overlays/ov020/auto/GetPanelBlockFlag200.c GetPanelBlockFlag200
python tools/verify_idx.py src/overlays/ov020/auto/Kind3Panel_OnSetActiveNoop.c Kind3Panel_OnSetActiveNoop
python tools/verify_idx.py src/overlays/ov020/auto/Kind3Panel_EntryEventTrue.c Kind3Panel_EntryEventTrue
bash tools/gate.sh
```
