.name        "test"
.comment    "test"

        fork %:son1    
        ld %0, r3                #carry a 1

live1:    live %-1
        zjmp %:live1            #live en boucle

son1:    live %-1
        fork %:son2
        aff r1
        sti r1, %:level2, %1    #sti en meme temps
        aff r1

son2:    aff r1
        sti r2, %:level2, %1    #sti en meme temps
        aff r1

level2:    live %42
