load "../plots/common.gnu"

plot    "./a1/quick_random" t "1" with lines lw 1,\
	    "./a16/quick_random" t "16" with lines lw 1,\
	    "./a256/quick_random" t "256" with lines lw 1
