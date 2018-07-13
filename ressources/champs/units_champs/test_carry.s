.name		"test_carry"
.comment	"test_carry"

carry:		and r2, r1, r2
			zjmp %:carry
