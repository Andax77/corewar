.name		"Fuck, Eat, Repeat"
.comment	"Basics..."

fuck:			

eat:			sti r1, %:live, %1
				ld  %1, r2
				sti r2, %124, r5				# build son's live
				sti r1, %122, r5				# build son's live's name
				ld  %-11, r4
				sti r4, %115, r5				# build sob's jump address
				ld  %9, r3
				sti r3, %100, r5				# build son's jump


live:			live %42
				ld %25, r6
				add r5, r6, r5					# calc next son's address

repeat:			lfork	%:eat					# fork back to eat
				sub r5, r6, r7					# catch the last son's adress
				ld  %20, r8						# calc offset for next jump
				add r7, r8, r7					# calc address for next jump
				sti r7, %:repeat, %48				# write address for next jump
				ld %9, r9						# load jump opcode
				sti r9, %:repeat, %46				# write jump
				add r10, r10, r10				# carry -> 1
