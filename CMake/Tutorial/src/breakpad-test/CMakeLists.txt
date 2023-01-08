add_executable(breakpad-test main.cpp)

message("CMAKE_BINARY_DIR : ${CMAKE_BINARY_DIR}")
message("CMAKE_CXX_COMPILER_ID : ${CMAKE_CXX_COMPILER_ID}")
message("CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC" AND CMAKE_BUILD_TYPE MATCHES "Release")
	target_compile_options(breakpad-test PRIVATE "$<$<CONFIG:Release>:/Zi>")
	target_link_options(breakpad-test PRIVATE "$<$<CONFIG:Release>:/DEBUG>")
	target_link_options(breakpad-test PRIVATE "$<$<CONFIG:Release>:/OPT:REF>")
	target_link_options(breakpad-test PRIVATE "$<$<CONFIG:Release>:/OPT:ICF>")
endif()

target_include_directories(breakpad-test
PUBLIC
	${CRASHPAD_INCLUDE_DIR}
	${CRASHPAD_MINI_CHROMIUM_INCLUDE_DIR}
	${CRASHPAD_CHROMEOS_BUILDFLAGS_INCLUDE_DIR}
)

target_link_libraries(breakpad-test
PUBLIC
	"${CRASHPAD_LIBRARY_DIR}/client/common.lib"
    "${CRASHPAD_LIBRARY_DIR}/client/client.lib"
	"${CRASHPAD_LIBRARY_DIR}/util/util.lib"
	"${CRASHPAD_LIBRARY_DIR}/third_party/mini_chromium/mini_chromium/base/base.lib"
)