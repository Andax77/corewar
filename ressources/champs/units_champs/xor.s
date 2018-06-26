.name		"xor"
.comment	"xor"

xor:		ld %42, r2
			ld %0, r3
			xor r2, r3, r4
			sti r4, %20, %0
