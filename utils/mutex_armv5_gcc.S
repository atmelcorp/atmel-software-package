#define LOCKED   1
#define UNLOCKED 0

#define TRUE     1
#define FALSE    0

/* try to lock mutex */
	.section .text.mutex_try_lock
	.global mutex_try_lock
mutex_try_lock:
	mov     r2, #LOCKED
	mov     r3, r0
	mov     r0, #TRUE
	swp     r1, r2, [r3]  /* Attempt to lock the mutex */
	cmp     r1, r2        /* Test if mutex is locked or unlocked */
	moveq   r0, #FALSE    /* If locked */
	bx      lr

/* unlock mutex */
	.section .text.mutex_unlock
	.global mutex_unlock
mutex_unlock:
	mov     r1, #UNLOCKED
	str     r1, [r0]      /* Unlock mutex */
	bx      lr

/* Check if mutex is locked or not */
	.section .text.mutex_is_locked
	.global mutex_is_locked
mutex_is_locked:
	mov     r2, #LOCKED
	mov     r3, r0
	mov     r0, #FALSE
	ldr     r1, [r3]
	cmp     r1, r2        /* Test if mutex is locked or unlocked */
	moveq   r0, #TRUE
	bx      lr
