	.text
	.globl	test_and_set

/**
 * test_and_set: assume it's called with test_and_set(&lock);
 * @param lock pointer to a mutex_t variable
 *
 * TODO - add a comment each line describing its action
 */
test_and_set:
	cli
	pushl	%ebx			# preserve contents of the %ebx register, which is about to be modified
	movl	8(%esp), %ebx	# store 8 + the stack pointer in ebx
	movl	$1, %eax		# store 1 in eax
	xchg	%eax, (%ebx)	# swap the contents of eax and ebx
	popl	%ebx			# retrieve the pushed contents back into ebx
	sti
	ret						# returns back to the place in the code it was called from
