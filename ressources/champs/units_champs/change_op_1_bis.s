.name		"change1bis"
.comment	"change1bis"

change1bis:	fork %:fork
			add r2, r2, r2
			ld  %42, r5
			zjmp %:write

fork:		and  r2, r2, r2
			ld  %1, r3
			sti r3, %:write, %0

write:		live %42
