/* Resolves a type-7 resource and passes a computed span to a helper; exact resource role unknown. Evidence: Source implementation directly performs the described operations; see src/calls/func_020255f0.c. Uncertainty: The exact game-specific role is unresolved. Recovered from Days source src/calls/func_020255f0.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern int func_0202d3e0(int unknown_argument_a, int unknown_argument_b, int unknown_argument_c);
extern int func_0201ac70(int resource_entry);
extern void func_0202a280(int unknown_argument_a, int unknown_argument_b, int unknown_argument_c, int unknown_argument_d);

void func_0202d3fc(int resource_id, int destination, int options) {
    int resource_entry = func_0202d3e0(resource_id, 7, 0);
    int resource_data;
    if (resource_entry == 0) return;
    resource_data = func_0201ac70(resource_entry);
    if (resource_data == 0) return;
    func_0202a280(destination, resource_id, resource_data + *(int *)(resource_data + 0x14) - resource_id, options);
}
