.name		"change_jmp"
.comment	"change_jmp"

change_jmp:	ld %9, r2
			sti r2, %:jmp, %5
			fork %:jmp
			ld %9, r2
			add r3, r3, r3
			ld %9, r2
			add r3, r3, r3
			ld %9, r2
			add r3, r3, r3
			ld %50, r4
			add r3, r3, r3

change:		sti r4, %:jmp, %7

jmp:		add r4, r4, r4
