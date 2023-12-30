
input.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <main>:
   0:	27bdfff0 	addiu	sp,sp,-16
   4:	afbe000c 	sw	s8,12(sp)
   8:	03a0f025 	move	s8,sp
   c:	afc00000 	sw	zero,0(s8)
  10:	afc00004 	sw	zero,4(s8)
  14:	1000000a 	b	40 <main+0x40>
  18:	00000000 	nop
  1c:	8fc30000 	lw	v1,0(s8)
  20:	8fc20004 	lw	v0,4(s8)
  24:	00000000 	nop
  28:	00621021 	addu	v0,v1,v0
  2c:	afc20000 	sw	v0,0(s8)
  30:	8fc20004 	lw	v0,4(s8)
  34:	00000000 	nop
  38:	24420001 	addiu	v0,v0,1
  3c:	afc20004 	sw	v0,4(s8)
  40:	8fc20004 	lw	v0,4(s8)
  44:	00000000 	nop
  48:	2842000a 	slti	v0,v0,10
  4c:	1440fff3 	bnez	v0,1c <main+0x1c>
  50:	00000000 	nop
  54:	8fc20000 	lw	v0,0(s8)
  58:	03c0e825 	move	sp,s8
  5c:	8fbe000c 	lw	s8,12(sp)
  60:	27bd0010 	addiu	sp,sp,16
  64:	03e00008 	jr	ra
  68:	00000000 	nop
  6c:	00000000 	nop
