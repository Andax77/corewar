.name		"sync"
.comment	"sync"

sync:		fork %:fork
			ld  %0, r2
			sti r1, %:write, %0
fork:		add r2, r2, r2
			zjmp %:write
write:		live %42
