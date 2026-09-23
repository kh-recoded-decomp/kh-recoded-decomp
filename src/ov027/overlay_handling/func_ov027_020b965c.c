/* Runs a helper on the first configured ID that is not -1, or returns zero. Evidence: Source implementation directly performs the described operations; see src/overlays/ov005/calls/func_ov005_0204e378.c. Uncertainty: The exact game-specific role is unresolved. Recovered from Days source src/overlays/ov005/calls/func_ov005_0204e378.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern int func_0204f228(int owner, int unknown_argument_b);
int func_ov027_020b965c(int owner, int *configured_ids) {
    int slot_index;
    int action_result;
    int unused_id;
    int candidate_id;
    action_result = 0;
    slot_index = action_result;
    unused_id = -1;
    do {
        candidate_id = configured_ids[slot_index + 5];
        if (candidate_id != unused_id) {
            action_result = func_0204f228(owner, candidate_id);
            break;
        }
        slot_index = slot_index + 1;
    } while (slot_index < 2);
    return action_result;
}
