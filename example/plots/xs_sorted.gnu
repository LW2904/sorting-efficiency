load "common.gnu"

set title "Various sorters with very small sorted sets."

plot 	"../data/linear/xs/insertion_sorted" t "insertion" with lines lw 1,\
	"../data/linear/xs/merge_sorted" t "merge" with lines lw 1,\
	"../data/linear/xs/quick_sorted" t "quick" with lines lw 1,\
	"../data/linear/xs/heap_sorted" t "heap" with lines lw 1