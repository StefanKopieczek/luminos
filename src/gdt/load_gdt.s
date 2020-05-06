// Used just to load the GDT to avoid inline ASM.

.global load_gdt
load_gdt:
  mov 4(%esp), %edx
  lgdt (%edx)

  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %ax, %ss
  jmp $0x08,$set_cs
set_cs:
  ret
