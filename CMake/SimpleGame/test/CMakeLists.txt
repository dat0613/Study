set(SOURCE_LIST
	"src/main.cpp"
)

add_executable(test ${SOURCE_LIST})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})
find_package(EnTT CONFIG REQUIRED)

if(EnTT_FOUND)
	target_link_libraries(test PUBLIC EnTT::EnTT)
else()
	message(FATAL_ERROR "EnTT not found")
endif()