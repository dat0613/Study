add_executable(breakpad-test main.cpp)

target_include_directories(breakpad-test
PUBLIC
	${CRASHPAD_INCLUDE_DIR}
	${CRASHPAD_MINI_CHROMIUM_INCLUDE_DIR}
	${CRASHPAD_CHROMEOS_BUILDFLAGS_INCLUDE_DIR}
)