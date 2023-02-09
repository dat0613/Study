set(SOURCE_LIST
	"src/main.cpp"
)

add_executable(test ${SOURCE_LIST})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})
find_package(EnTT CONFIG REQUIRED)

if(EnTT_FOUND)
	message("Found : ${ENTT_INCLUDE_HEADERS}")
	message("Found : ${ENTT_INCLUDE_DIRS}")
	message("Found : ${CMAKE_CURRENT_SOURCE_DIR}")
	message("${CMAKE_SOURCE_DIR}")
endif()

target_link_libraries(test PRIVATE EnTT)
target_include_directories(test PUBLIC
                                            include
                                            EnTT::EnTT )