load "common.gnu"

set title "Various sorters with very small sorted sets."

plot 	"../data/xs/insertion_sorted" t "insertion" with linespoints lw 1,\
	"../data/xs/merge_sorted" t "merge" with linespoints lw 1,\
	"../data/xs/quick_sorted" t "quick" with linespoints lw 1,\
	"../data/xs/heap_sorted" t "heap" with linespoints lw 1