add_library(shared-library-example SHARED 
share.cpp 
include/share.hpp)

#target_include_directories(shared-library-example PUBLIC ${CMAKE_SOURCE_DIR}/shared-library-example/include)