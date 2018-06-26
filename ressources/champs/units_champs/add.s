.name		"add"
.comment	"add"

add:		ld %21, r2
			ld %21, r3
			add r2, r3, r4
			sti r4, %20, %0
