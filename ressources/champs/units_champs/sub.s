.name		"sub"
.comment	"sub"

sub:		ld %84, r2
			ld %42, r3
			sub r2, r3, r4
			sti r4, %20, %0
