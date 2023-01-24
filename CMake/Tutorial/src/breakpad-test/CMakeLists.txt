add_executable(breakpad-test 
main.cpp
private_environment.hpp
)

message("CMAKE_BINARY_DIR : ${CMAKE_BINARY_DIR}")
message("CMAKE_CXX_COMPILER_ID : ${CMAKE_CXX_COMPILER_ID}")
message("CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(breakpad-test PRIVATE "/Zi")
	target_link_options(breakpad-test PRIVATE "/DEBUG")
	target_link_options(breakpad-test PRIVATE "/OPT:REF")
	target_link_options(breakpad-test PRIVATE "/OPT:ICF")

	target_link_libraries(breakpad-test
	PUBLIC
		"${CRASHPAD_LIBRARY_DIR}/client/common.lib"
		"${CRASHPAD_LIBRARY_DIR}/client/client.lib"
		"${CRASHPAD_LIBRARY_DIR}/util/util.lib"
		"${CRASHPAD_LIBRARY_DIR}/third_party/mini_chromium/mini_chromium/base/base.lib"
)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	target_compile_options(breakpad-test PRIVATE -g)

	target_link_libraries(breakpad-test
	PUBLIC
		"${CRASHPAD_LIBRARY_DIR}/client/libcommon.a"
		"${CRASHPAD_LIBRARY_DIR}/client/libclient.a"
		"${CRASHPAD_LIBRARY_DIR}/util/libutil.a"
		"${CRASHPAD_LIBRARY_DIR}/third_party/mini_chromium/mini_chromium/base/libbase.a"
)
endif()

target_include_directories(breakpad-test
PUBLIC
	${CRASHPAD_INCLUDE_DIR}
	${CRASHPAD_MINI_CHROMIUM_INCLUDE_DIR}
	${CRASHPAD_CHROMEOS_BUILDFLAGS_INCLUDE_DIR}
)