.name		"test_carry"
.comment	"test_carry"

carry:		ldi %42, %0, r2
			zjmp %:carry
