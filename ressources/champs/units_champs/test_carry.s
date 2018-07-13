.name		"test_carry"
.comment	"test_carry"

carry:		ld %0, r2
			fork %:zjmp
zjmp:		zjmp %:carry
