.name		"fork"
.comment	"fork"

fork:		live %1
			add r2, r2, r2
			fork %:fork
