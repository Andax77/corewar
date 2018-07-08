.name		"change1ter"
.comment	"change1ter"

change1ter:	fork %:fork
			ld  %42, r5
			add r2, r2, r2
			zjmp %:write

fork:		and  r2, r2, r2
			ld  %1, r3
			sti r3, %:write, %-3

write:		
