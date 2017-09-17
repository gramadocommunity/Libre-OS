#ifndef ARCH_I386_IDT_H
#define ARCH_I386_IDT_H

#include "../libc/include/sys/cdefs.h"
typedef struct {
	#ifdef __IX86__
	uint16_t base_low;
	uint16_t sel;
	uint8_t zero;
	uint8_t flags;
	uint16_t base_high;
	#endif
} __attribute__((packed)) idt_entry_t;

typedef struct {
	#ifdef __IX86__
	uint16_t limit;
	uintptr_t base;
	#endif
} __attribute__((packed)) idt_pointer_t;

/* In the future we may need to put a lock on the access of this */
static struct {
	#ifdef __IX86__
	idt_entry_t entries[256];
	idt_pointer_t pointer;
	#endif
} idt __attribute__((used));

#define ENTRY(X) (idt.entries[(X)])

typedef void (*idt_gate_t)(void);

extern void idt_load(uintptr_t);


void idt_set_gate(uint8_t num, idt_gate_t base, uint16_t sel, uint8_t flags) {
	ENTRY(num).base_low = ((uintptr_t)base & 0xFFFF);
	ENTRY(num).base_high = ((uintptr_t)base >> 16) & 0xFFFF;
	ENTRY(num).sel = sel;
	ENTRY(num).zero = 0;
	ENTRY(num).flags = flags | 0x60;
}

void idt_install(void) {
	idt_pointer_t * idtp = &idt.pointer;
	idtp->limit = sizeof idt.entries - 1;
	idtp->base = (uintptr_t)&ENTRY(0);
	memset(&ENTRY(0), 0, sizeof idt.entries);

	idt_load((uintptr_t)idtp);
}


#undef ENTRY


#endif //idt