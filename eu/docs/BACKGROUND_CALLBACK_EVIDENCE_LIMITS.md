# Follow-up evidence for the six retained callback functions

The two separately supported closures are `StopStageBrightnessFade`
(ov041:020bcd78) and `SetCameraGoalSnapEnabled` (ov042:020be4bc). The
remaining six identities retain their names because their specific missing
contracts have not been established.

## The two ov002 background hooks

The construction chain is now explicit. `InitMenuContext` constructs its
main background at menuWork+0x4d4 and sub background at +0x520. Both configs
contain the two empty ARM function addresses; `InitBackgroundContainer`
copies those config words into this same runtime object's +0x3c/+0x40.
The generic ov027 `TagTracker_InvokeCallback` and `InvokeCallback40` read
these offsets. Matching offsets in another concrete object, such as the
FieldSceneManager, do not prove a call on either menu background object.

The exact ov002 release path is also known:
`ReleaseContextResources` -> `FreeTagTrackerPools` -> `SweepElements` ->
`DeactivateAllTrackerRecords(container,0)` ->
`DeactivateTrackerRecord(container,record,0)`. The last helper only calls
container +0x40 when its third argument is nonzero. This owning path
therefore suppresses the hook. `AnimateMenuBgFrames` uses subBg+0x520 for
screen lookup and direct `GXS_LoadBG1Scr`, without calling either hook.

All 232 currently configured ov002 function bodies were checked against
the original EU bytes. None has an original-index direct relocation to
the seven identified channel/sequence invokers. This excludes historical
index aliases from the count. It does not exclude a computed call or an
unproved external owner binding.

For `func_ov002_02065c4c` and `func_ov002_02065c50`, the remaining proof is
a native call/data-flow chain passing these exact menu background objects
to the relevant invoker. An init/update/draw/cleanup label still exceeds
what has been demonstrated.

Sources:

- `eu/src/overlays/ov002/calls/InitMenuContext.c`
- `eu/src/overlays/ov002/calls/ReleaseContextResources.c`
- `eu/src/overlays/ov002/calls/AnimateMenuBgFrames.c`
- `eu/src/overlays/ov027/calls/InitBackgroundContainer.c`
- `eu/src/overlays/ov027/calls/FreeTagTrackerPools.c`
- `eu/src/overlays/ov027/calls/SweepElements.c`
- `eu/src/overlays/ov027/calls/DeactivateAllTrackerRecords.c`
- `eu/src/overlays/ov027/auto/DeactivateTrackerRecord.c`
- `eu/src/overlays/ov027/auto/TagTracker_InvokeCallback.c`
- `eu/src/overlays/ov027/auto/InvokeCallback40.c`

## The two ov043 leaves and two ov044 writers

Fresh explicit-bank Ghidra queries report no references to the two
ov043 leaves, or to ov044 table 020d0df8 and its slot 2/slot 3 words. This
does not prove unreachability. It adds no constructor, selected-slot
caller or output consumer and therefore supports no new role name.

The ov043 literal-zero leaf still needs an owning caller/registered slot;
the empty leaf still needs its own slot/caller and argument/result use.
The two ov044 five-word writers still need their table invoker and the
incoming-R0 destination owner. The already excluded ov036 texture-loader
and ov052 same-RAM hits do not fill those gaps. No repeated broad raw
reference search was used in this follow-up.

The current integration changes none of these six bodies or declarations. Seventeen functions in the background construction/release chain were compared in full with the original ROM; the current ov002 inventory has 232 unique configured functions, rather than 322 historical index entries including aliases. The linked gate retains all 108 module hashes. The two separately closed names have fresh official checks in their linked contracts.
