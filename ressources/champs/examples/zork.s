.name "zork"
.comment "I'M ALIIIIVE"

l2:		live %3	
	sti r13, %300, %900
		and r1, %0, r1

live:	live %1
		zjmp %:l2
