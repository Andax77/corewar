.name		"Fuck, Eat, Repeat"
.comment	"Basics..."

eat:			sti r1, %:repeat, %4			# names live
				sti r1, %:eat, %15				# names live
				live %42
				ld  %1, r2						# load live opcode in r2
				sti r2, %124, r5				# build son's live
				sti r1, %122, r5				# build son's live's name
				ld  %-11, r4					# load son's zjmp value
				sti r4, %115, r5				# build son's zjmp address
				ld  %9, r3						# load zjmp opcode inr r3
				sti r3, %100, r5				# build son's jump
				ld %25, r6						# set son's offset
				add r5, r6, r5					# calc next son's address

repeat:			fork	%:eat					# fork back to eat
				live %42
				sub r5, r6, r7					# catch the last son's adress
				ld  %25, r8						# calc offset for next zjmp
				add r7, r8, r7					# calc address for next zjmp
				sti r7, %:repeat, %53			# write address for next zjmp
				ld %9, r9						# load jump opcode
				sti r9, %:repeat, %51			# write jump
				add r10, r10, r10				# carry -> 1
