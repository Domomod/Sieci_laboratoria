# cmake version to be used
<<<<<<< Updated upstream
cmake_minimum_required( VERSION 3.10 )

=======
cmake_minimum_required( VERSION 3.14 )
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
>>>>>>> Stashed changes
# project name
 project( Sieci_laboratoria )

# flags

# files

# include
include_directories( ./include ./src  )

# target
add_executable( main ./src/main.cpp ./src/CMIBobject.cpp ./src/CMIBTree.cpp ./src/CTrieNode.cpp)

# external libs
#add_subdirectory( ./libs/Logger )
#target_link_libraries( binary logger )

# add_subdirectory( ./libs/Randomize )
# target_link_libraries( binary randomize )

#add_library(randomize STATIC IMPORTED)
#set_property(TARGET randomize PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/Randomize/librandomize.a)
#target_link_libraries( binary randomize )

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)