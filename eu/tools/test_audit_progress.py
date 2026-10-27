"""Keep register annotations distinct from assembly instructions in progress."""
import unittest

from audit_progress import contains_assembly


class RegisterBindingClassification(unittest.TestCase):
    def test_complete_register_declarations_are_c(self):
        for declaration in [
            'register u32 mask __asm("r1");',
            'register volatile u32 *bitmap __asm("r3");',
            'register unsigned int value __asm("r2");',
        ]:
            with self.subTest(declaration=declaration):
                self.assertFalse(contains_assembly(declaration))

    def test_c_without_annotations_is_unchanged(self):
        self.assertFalse(contains_assembly('void Clear(unsigned *value) { *value = 0; }'))

    def test_assembly_after_a_binding_is_still_detected(self):
        binding = 'register u32 value __asm("r2");'
        self.assertTrue(contains_assembly(binding + '\n__asm("nop");'))
        self.assertTrue(contains_assembly(binding + ' __asm("nop");'))

    def test_instruction_and_malformed_annotations_remain_assembly(self):
        for source in [
            '__asm("nop");',
            'asm void Routine(void) { bx lr }',
            'register u32 value __asm("r2\\nnop");',
            'register u32 value __asm("r16");',
            'register u32 value __asm("r2") = 0;',
        ]:
            with self.subTest(source=source):
                self.assertTrue(contains_assembly(source))


if __name__ == '__main__':
    unittest.main()
