# cmake version to be used
cmake_minimum_required( VERSION 3.14 )
# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# project name
project( Sieci_laboratoria )

################################
# GTest
################################
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  # Use latest commit of v1.10.X branch
  URL https://github.com/google/googletest/archive/04e52ebe78166f0eb602dfc35817f91cc575cbfb.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# include
include_directories( ./include ./src ./test )

################################
# Unit Tests
################################
# Add test cpp file
add_executable( runTest 
./test/cmib_parser_test.cpp 
./src/cmib_parser.cpp    ./include/cmib_parser.hpp 
./src/cmib_sequencer.cpp ./include/cmib_sequencer.hpp
                         ./include/cmib_regex.hpp
                         ./include/types.hpp )
# Link test executable against gtest & gtest_main
target_link_libraries(runTest gtest gtest_main)
add_test( runTest runTest )

################################
# Build
################################

# flags

# files

# target
add_executable( main
./src/main.cpp 
./src/cmib_object.cpp 
./src/cmib_tree.cpp 
./src/ctree_node.cpp
./src/cmib_parser.cpp  
./src/cmib_sequencer.cpp)


# external libs
#add_subdirectory( ./libs/Logger )
#target_link_libraries( binary logger )

# add_subdirectory( ./libs/Randomize )
# target_link_libraries( binary randomize )

#add_library(randomize STATIC IMPORTED)
#set_property(TARGET randomize PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/Randomize/librandomize.a)
#target_link_libraries( binary randomize )

