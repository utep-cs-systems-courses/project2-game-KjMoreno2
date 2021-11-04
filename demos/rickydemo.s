/*	void oncePerSecond()
	{
	blinkLimit++		;
	if(blinkLimit >= 0) {
	    blinkLimit =0	;
	}
	}

	*/
/*
oncePerSecond:
	blinkLimit += 1		;
	if (blinkLimit <8) goto Out ;
	blinkLimit=0		    ;
out:
	return			;
	*/
	//you would need to define blinklimit in the header file
/*
		.extern blinkLimit
		.global oncePerSecond
oncePerSecond:
	add #1, &blinkLimit
	cmp #8, &blinkLimit
	jnc out
	mov #0, &blinkLimit
Out:
	ret //pop from the stack into r0(return) or ret
	*/
// REFRENCE THIS FOR PROJECT2 AND ASSEMBLY
