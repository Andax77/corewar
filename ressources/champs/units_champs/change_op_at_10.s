.name		"change10"
.comment	"change10"

change10:	fork %:fork
			add r2, r2, r2
			zjmp %:write

fork:		ld  %0, r2
			ld  %0, r2
			ld  %0, r2
			sti r1, %:write, %0

write:		live %42
