.name		"change1"
.comment	"change1"

change1:		fork %:fork
			add r2, r2, r2
			zjmp %:write

fork:		and  r2, r2, r2
			sti r1, %:write, %0

write:		live %42
