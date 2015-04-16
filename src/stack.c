/* @(#) stack.c 1.4@(#) 01/03/04
 * PBL Interpreter
 *
 *  stack.c
 *  stack implementation
 *
 * John Willis
 * willisj@atlantis.clogic-int.com
 *
 * 2/10/1999	11:40 AM	initial work
 */

#include "glob.h"

/* push():	places a numeric value on the internal stack */
void push(int value)
{
	/* if a stack is available */
	if(stackindex <= _STACKS)
	{	
		/* increment the stack count */
		stackindex++;
	
		/* place the value on the stack */
		stack[stackindex] = value;
	}
	else /* if a stack is not available */
	{
		/* display an error message */
		printf("Error:  internal stack overflow\n");
	
		/* terminate */
		exit(0);
	}

} /* push() */

/* pop():	pops a value off the internal stack */
int pop(void)
{
	/* if the stack is not empty */
	if(stackindex >= 1)
	{
		/* decrement the stack count */
		stackindex--;

		/* return the value */
		return stack[stackindex + 1];
	}
	else
	{
		/* print an error message */
		printf("attempted to pop off an empty stack\n");
	
		/* abort */
		exit(0);
	}
} /* pop() */
	
