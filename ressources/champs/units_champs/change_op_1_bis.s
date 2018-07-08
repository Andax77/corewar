.name		"change1bis"
.comment	"change1bis"

change1bis:	fork %:fork
			ld  %42, r5
			add r2, r2, r2
			zjmp %:write

fork:		and  r2, r2, r2
			ld  %1, r3
			sti r3, %:write, %0

write:		
