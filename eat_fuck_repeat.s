.name		"Eat, Fuck, Repeat"
.comment	"Basics..."

saymyname:		sti r1, %:live, %1
				ld  %1, r2
				sti r2, %255, %0
				sti r1, %252, %0
				ld  %9, r4
				sti r4, %239, %3
				ld  %0, r5
				sti r5, %232, %0

live:			live			%1

fuck:			fork	%:saymyname
