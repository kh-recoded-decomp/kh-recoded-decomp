# Overlay 053 special-action callback bank

One existing relocation annotation in overlay 053 selected the wrong bank. At native address 0x020d22f4, InitOverlay053Entity stores the Thumb pointer 0x020a1859 in actor+0x10fc. The former metadata described overlay 006 data base 0x020a1854 plus 5; the corrected metadata describes overlay 010 function 0x020a1858 plus 1. Both expressions preserve all four original ROM bytes, `59 18 0a 02`.

The bank follows from a concrete loader and consumer chain:

1. Slot-7 binding record 6 selects gOv010ScriptObjectCreationHandlers and overlay ID 10. BindScriptHandlersSlot7 requests that overlay before recording index 6 in session+0x18. Index 6 and overlay ID 10 are separate domains.
2. InitOverlay053Entity installs the callback only when the recorded index is 6 and flag 0x3715 is set. It also installs companion Entity_ChangeSpecialState at actor+0x10ec; the companion reference already selected overlay 010.
3. TryStartSpecialAction and SelectGroundAction invoke actor+0x10fc as BOOL(actor). Entity_HandleSpecialAction in overlay 010 reads the companion and can invoke it with (actor, 0x1e).
4. The same RAM location in overlay 006 lies inside sOv006ElevatorFrameData. Its original words are data, not the function entrypoint used by this protocol.

The binding stores its index after the load call returns without checking the status. This establishes the selected bank, not guaranteed loading after a runtime failure. No new loading check or behavior is introduced.

Only one configuration line changes, retaining its origin, load kind and complete native pointer value. This corrects a specific erroneous annotation; it does not choose arbitrarily among overlapping banks. Neither the C callback expression nor its existing declarations, any source body, compiler selection or verifier is changed to hide the discrepancy. Native void callback views still need consistent typed reconciliation for a host ABI.

An original-source control at the actual compilation path reproduced the old standalone mismatch. That control was diagnostic, not a baseline waiver. After the bank correction, all 28 affected official function checks pass, including InitOverlay053Entity (232 bytes, 16 relocations). All 28 complete objects retain allocated bytes/alignment, symbol layouts and relocation target values/types/addends. A fresh gate passes 108/108 native modules with every hash unchanged.

## Active evidence

- [Binding loader](../src/overlays/ov001/calls/BindScriptHandlersSlot7.c).
- [Recorded index reader](../src/overlays/ov001/calls/GetScriptHandlerSlot7Index.c).
- [Guarded callback installation](../src/overlays/ov053/calls/InitOverlay053Entity.c).
- [Overlay 010 callback](../src/overlays/ov010/calls/Entity_HandleSpecialAction.c).
- [Corrected relocation annotation](../config/arm9/overlays/ov053/relocs.txt).

The original-ROM review compares ten complete functions and five complete extracted overlay modules. Its loader row at ov001:0209d928 has raw bytes `a0 1d 0a 02 0a 00 00 00`, establishing handler-table pointer 0x020a1da0 and overlay ID 10. Reader, writer and loader evidence are independent of equal RAM addresses.
