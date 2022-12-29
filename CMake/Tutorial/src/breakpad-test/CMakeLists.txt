add_executable(breakpad-test main.cpp)

target_include_directories(breakpad-test
PUBLIC
	${CRASHPAD_INCLUDE_DIR}
)