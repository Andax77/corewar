.name "zork"
.comment "I'M ALIIIIVE"

        aff r1
        aff r3
        ld %42, r2
        ld %42, r2
        aff r2
l2:     sti r1, %:live, %1
        and r1, %0, r1

live:   live %1
        zjmp %:live
