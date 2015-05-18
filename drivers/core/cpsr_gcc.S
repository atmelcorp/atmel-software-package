	.global v_arm_clr_cpsr_bits
	.global v_arm_set_cpsr_bits
	.global v_arm_read_control
	.global v_arm_write_control

v_arm_clr_cpsr_bits:
	push	{r1}
	mrs	r1, cpsr
	mvn	r0, r0
	and	r1, r1,r0
	msr	CPSR_c, r1
	pop	{r1}
	bx	lr

v_arm_set_cpsr_bits:
	push	{r1}
	mrs	r1, cpsr
	orr	r1, r1, r0
	msr	cpsr_c, r1
	pop	{r1}
	bx	lr

v_arm_read_control:
	mov	r0,#0
	mrc	p15, 0, r0, c1, c0, 0
	bx	lr

v_arm_write_control:
	mcr	p15, 0, r0, c1, c0, 0
	bx	lr
