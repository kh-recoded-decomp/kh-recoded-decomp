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
