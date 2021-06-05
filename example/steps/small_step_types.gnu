load "../plots/common.gnu"

set xlabel "Chunk index"
set ylabel "Chunk size"

plot [0:32] (262144 / 128**2) * x**2 t "quadratic",\
        (262144 / 128) * x t "linear"