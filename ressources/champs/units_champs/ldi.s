.name		"ldi"
.comment	"ldi"

ldi:		ld %42, r2
			sti r2, %20, %0
			ldi %20, %-7, r3
			sti r3, %30, %0
