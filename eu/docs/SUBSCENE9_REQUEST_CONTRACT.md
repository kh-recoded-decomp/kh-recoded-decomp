# Subscene-9 request availability

The names are `IsSubScene9RequestBusy` (ov001:02066e70, Thumb, 28 B) and
`ScriptCmd_WaitForSubScene9RequestReady` (ov001:020655c4, Thumb, 18 B).
The existing definitions are unsigned-int(void) and int(void), respectively.

The owner is gSubScene9Work at 020a0488, a task-work pointer initialized by
SubScene9_Create_02066c80; it is separate from the message-sprite manager.
The constructor sets state byte 0=0 and initializes a tween at +8. The predicate
returns 1 exactly for signed states other than 0 and 3. Its real consumer
SubScene9_Request rejects a new request when that predicate is true; otherwise
it stores request byte 1, writes state 1 and returns 1. This proves the narrow
request-busy contract without inventing a meaning for state 3.

The normal callback chain consumes state 1, sets 2 and runs the two brightness
tweens with a timed hold. The last step returns state 0 once the tween completes
and the request byte is 0. The existing native state values and timing remain
unchanged. No narrative identity for SubScene9 is inferred.

Group 2/entry 0x23 has ScriptCmd_RequestSubScene9 as run and 020655c4 as resume
(flat indices 70/71), verified against the original ROM words. Run reads its
wait operand, attempts Request(0) and ignores whether that request was accepted.
It returns 1 immediately for a zero wait operand. The resume consumes no logical
inputs and returns !busy. It therefore waits for request availability; it does
not guarantee that the run call successfully queued a new request of its own.

The work pointer must already exist: this predicate is not IsSubScene9TaskActive
and has no NULL check. State3 remains an available state with no additional
lifecycle label. This rename preserves existing ABI, private typedefs and shared ROOT bodies.
Ten original functions and the paired script-table words were checked against
the native ROM. Availability does not imply task existence or request success.

- [Request-busy predicate](../src/overlays/ov001/calls/IsSubScene9RequestBusy.c).
- [Script resume](../src/overlays/ov001/calls/ScriptCmd_WaitForSubScene9RequestReady.c).
- [Actual request consumer](../src/overlays/ov001/calls/SubScene9_Request.c).

## Byte-exact validation

All ten affected official function checks pass. All 12 complete objects preserve allocated bytes/alignment, symbol layouts and relocation targets/types/addends. A fresh gate passes all 108 modules with identical hashes. Source bodies, signatures and shared ROOT implementations are preserved. From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/IsSubScene9RequestBusy.c IsSubScene9RequestBusy --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_WaitForSubScene9RequestReady.c ScriptCmd_WaitForSubScene9RequestReady --thumb
bash tools/gate.sh
```
