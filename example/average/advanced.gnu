load "../plots/common.gnu"

set multiplot layout 4,3

set title "sorted"
plot    "./advanced/1/quick_sorted" t "q1" with lines lw 1,\
        "./advanced/16/quick_sorted" t "q16" with lines lw 1,\
        "./advanced/1024/quick_sorted" t "q1024" with lines lw 1
set title "random"
plot    "./advanced/1/quick_random" t "q1" with lines lw 1,\
        "./advanced/16/quick_random" t "q16" with lines lw 1,\
        "./advanced/1024/quick_random" t "q1024" with lines lw 1
set title "inverted"
plot    "./advanced/1/quick_inverted" t "q1" with lines lw 1,\
        "./advanced/16/quick_inverted" t "q16" with lines lw 1,\
        "./advanced/1024/quick_inverted" t "q1024" with lines lw 1

set title "sorted"
plot    "./advanced/1/insertion_sorted" t "s_i1" with lines lw 1,\
        "./advanced/16/insertion_sorted" t "s_i16" with lines lw 1,\
        "./advanced/1024/insertion_sorted" t "s_i1024" with lines lw 1
set title "random"
plot    "./advanced/1/insertion_random" t "i1" with lines lw 1,\
        "./advanced/16/insertion_random" t "i16" with lines lw 1,\
        "./advanced/1024/insertion_random" t "i1024" with lines lw 1
set title "inverted"
plot    "./advanced/1/insertion_inverted" t "i1" with lines lw 1,\
        "./advanced/16/insertion_inverted" t "i16" with lines lw 1,\
        "./advanced/1024/insertion_inverted" t "i1024" with lines lw 1

set title "sorted"
plot    "./advanced/1/merge_sorted" t "m1" with lines lw 1,\
        "./advanced/16/merge_sorted" t "m16" with lines lw 1,\
        "./advanced/1024/merge_sorted" t "m1024" with lines lw 1
set title "random"
plot    "./advanced/1/merge_random" t "m1" with lines lw 1,\
        "./advanced/16/merge_random" t "m16" with lines lw 1,\
        "./advanced/1024/merge_random" t "m1024" with lines lw 1
set title "inverted"
plot    "./advanced/1/merge_inverted" t "m1" with lines lw 1,\
        "./advanced/16/merge_inverted" t "m16" with lines lw 1,\
        "./advanced/1024/merge_inverted" t "m1024" with lines lw 1

set title "sorted"
plot    "./advanced/1/heap_sorted" t "h1" with lines lw 1,\
        "./advanced/16/heap_sorted" t "h16" with lines lw 1,\
        "./advanced/1024/heap_sorted" t "h1024" with lines lw 1
set title "random"
plot    "./advanced/1/heap_random" t "h1" with lines lw 1,\
        "./advanced/16/heap_random" t "h16" with lines lw 1,\
        "./advanced/1024/heap_random" t "h1024" with lines lw 1
set title "inverted"
plot    "./advanced/1/heap_inverted" t "h1" with lines lw 1,\
        "./advanced/16/heap_inverted" t "h16" with lines lw 1,\
        "./advanced/1024/heap_inverted" t "h1024" with lines lw 1
