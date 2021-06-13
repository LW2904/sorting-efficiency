../../build/benchmark -t linear -s 16384 -c 32 -o ./default/1
../../build/benchmark -t linear -s 16384 -c 32 -a 2 -o ./default/2
../../build/benchmark -t linear -s 16384 -c 32 -a 4 -o ./default/4
../../build/benchmark -t linear -s 16384 -c 32 -a 8 -o ./default/8
../../build/benchmark -t linear -s 16384 -c 32 -a 16 -o ./default/16
../../build/benchmark -t linear -s 16384 -c 32 -a 1024 -o ./default/1024

../../build/benchmark -r -t linear -s 16384 -c 32 -o ./advanced/1
../../build/benchmark -r -t linear -s 16384 -c 32 -m 2 -o ./advanced/2
../../build/benchmark -r -t linear -s 16384 -c 32 -m 4 -o ./advanced/4
../../build/benchmark -r -t linear -s 16384 -c 32 -m 8 -o ./advanced/8
../../build/benchmark -r -t linear -s 16384 -c 32 -m 16 -o ./advanced/16
../../build/benchmark -r -t linear -s 16384 -c 32 -m 1024 -o ./advanced/1024
