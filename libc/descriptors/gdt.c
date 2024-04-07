#define GDT_FLAG_DATASEG 0x02
#define GDT_FLAG_CODESEG 0x0a
#define GDT_FLAG_TSS     0x09

#define GDT_FLAG_SEGMENT 0x10
#define GDT_FLAG_RING0   0x00
#define GDT_FLAG_RING3   0x60
#define GDT_FLAG_PRESENT 0x80

#define GDT_FLAG_4K_GRAN 0x800
#define GDT_FLAG_32_BIT  0x400

#define GDT_ENTRIES 7

static unsigned long long gdt[GDT_ENTRIES];

static void set_entry(int i, unsigned base, unsigned int limit, int flags)
{
  gdt[i] = limit & 0xffffLL;
  gdt[i] |= (base & 0xffffffLL) << 16;
  gdt[i] |= (flags & 0xffLL) << 40;
  gdt[i] |= ((limit >> 16) & 0xfLL) << 48;
  gdt[i] |= ((flags >> 8) & 0xffLL) << 52;
  gdt[i] |= ((base >> 24) & 0xffLL) << 56;
}

void load_gdt()
{
  struct {
    unsigned short limit;
    void* pointer;
  } __attribute__((packed)) gdtp = {
    .limit = sizeof(gdt)-1,
    .pointer = gdt,
  };
  asm volatile("lgdt %0" : : "m" (gdtp));
  asm volatile("mov $0x10, %ax");
  asm volatile("mov %ax, %ds");
  asm volatile("mov %ax, %es");
  asm volatile("mov %ax, %fs");
  asm volatile("mov %ax, %gs");
  asm volatile("mov %ax, %ss");
  asm volatile("ljmp $0x8, $.1; .1:");
}

void init_gdt(void)
{
  set_entry(0, 0, 0, 0);
  set_entry(1, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
            GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
  set_entry(2, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
            GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
  set_entry(3, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
            GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
  set_entry(4, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | 
            GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);

  load_gdt();
}
