add_executable(breakpad-test main.cpp)

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