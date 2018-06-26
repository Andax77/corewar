.name		"or"
.comment	"or"

or:			ld %42, r2
			ld %42, r3
			or r2, r3, r4
			sti r4, %20, %0
