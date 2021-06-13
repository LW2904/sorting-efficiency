load "../plots/common.gnu"

plot    "./run1/quick_random" t "run 1" with lines lw 1,\
	    "./run8/quick_random" t "run 8" with lines lw 1,\
	    "./run16/quick_random" t "run 16" with lines lw 1
