.name		"20_lives"
.comment	"20_lives"

20_lives:	fork %:jmp
			live %-1
			live %-1
			live %-1
			live %-1
			live %-1
			live %-1
			live %-1
			live %-1
			live %-1
			live %-1
			and r2, r2, r2
			zjmp %800
jmp:		live %-1
			live %-1
			live %-1
			live %-1
			live %-1
			live %-1
			live %-1
			live %-1
			live %-1
			live %-1
			live %42
