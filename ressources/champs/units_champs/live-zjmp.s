.name			"live-zjmp"
.comment		"live-zjmp"

live:		live %42
			sti  r1, %:live, %1
			ld   %0, r0
			zjmp %:live
