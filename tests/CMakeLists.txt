# This exclusively contains the catch2 main define, separated because precompiling
# headers would be a problem otherwise.
add_library(tests-main STATIC main.cpp)

# This contains the actual tests and implementation files.
add_executable(tests-run sets.cpp sorters.cpp utils.cpp
	../src/benchmark.cpp ../src/config.cpp ../src/utils/experiment.cpp
	../src/probands/sets.cpp ../src/probands/sorters.hpp)

set_target_properties(tests-run PROPERTIES CXX_STANDARD 17)
target_compile_features(tests-run PRIVATE cxx_std_17)

target_link_libraries(tests-run tests-main)

target_compile_definitions(tests-run PRIVATE CATCH_CONFIG_FAST_COMPILE
	CATCH_CONFIG_DISABLE_MATCHERS)

# Important if you don't want the test compile to take >5s every time.
target_precompile_headers(tests-run PRIVATE deps/catch.h)

add_custom_target(test "tests-run" "-d yes")
