// Used just to load the GDT to avoid inline ASM.

.global load_gdt
load_gdt:
  mov 4(%esp), %edx
  lgdt (%edx)
  ret
