
fib.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <main>:
   0:	27bdffd8 	addiu	sp,sp,-40
   4:	afbf0024 	sw	ra,36(sp)
   8:	afbe0020 	sw	s8,32(sp)
   c:	03a0f021 	move	s8,sp
  10:	2402000a 	li	v0,10
  14:	afc20018 	sw	v0,24(s8)
  18:	8fc40018 	lw	a0,24(s8)
  1c:	201c0044	addi	gp,zero,64
  20:   0380f809	jalr	ra,gp
  24:	00000000 	nop
  28:	afc2001c 	sw	v0,28(s8)
  2c:	03c0e821 	move	sp,s8
  30:	8fbf0024 	lw	ra,36(sp)
  34:	8fbe0020 	lw	s8,32(sp)
  38:	27bd0028 	addiu	sp,sp,40
  3c:	03e00008 	jr	ra
  40:	00000000 	nop

00000040 <fib>:
  44:	27bdffd0 	addiu	sp,sp,-48
  48:	afbf002c 	sw	ra,44(sp)
  4c:	afbe0028 	sw	s8,40(sp)
  50:	afb00024 	sw	s0,36(sp)
  54:	03a0f021 	move	s8,sp
  58:	afc40030 	sw	a0,48(s8)
  5c:	8fc20030 	lw	v0,48(s8)
  60:	00000000 	nop
  64:	28420003 	slti	v0,v0,3
  68:	10400005 	beqz	v0,7c <fib+0x38>
  6c:	00000000 	nop
  70:	24020001 	li	v0,1
  74:	08000031 	j	c4 <fib+0x78>
  78:	00000000 	nop
  7c:	8fc20030 	lw	v0,48(s8)
  80:	00000000 	nop
  84:	2442ffff 	addiu	v0,v0,-1
  88:	00402021 	move	a0,v0
  8c:	201c0040	addi	gp,zero,64
  90:	0380f809	jalr	ra,gp
  94:	00000000	nop
  98:	00408021 	move	s0,v0
  9c:	8fc20030 	lw	v0,48(s8)
  a0:	00000000 	nop
  a4:	2442fffe 	addiu	v0,v0,-2
  a8:	00402021 	move	a0,v0
  ac:	201c0044	addi	gp,zero,64
  b0:	0380f809	jalr	ra,gp
  b4:	00000000 	nop
  b8:	02021021 	addu	v0,s0,v0
  bc:	afc20018 	sw	v0,24(s8)
  c0:	8fc20018 	lw	v0,24(s8)
  c4:	03c0e821 	move	sp,s8
  c8:	8fbf002c 	lw	ra,44(sp)
  cc:	8fbe0028 	lw	s8,40(sp)
  d0:	8fb00024 	lw	s0,36(sp)
  d4:	27bd0030 	addiu	sp,sp,48
  d8:	03e00008 	jr	ra
  dc:	00000000 	nop
	...
