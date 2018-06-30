.name		"test_carry"
.comment	"test_carry"

carry:		lldi %42, %0, r2
			zjmp %:carry
