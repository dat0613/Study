set(SOURCE_LIST
	"src/main.cpp"
	"src/Base/Type.hpp"
	"src/Base/GameBase.cpp"
	"src/Base/GameBase.hpp"
	"src/Base/Renderer.cpp"
	"src/Base/Renderer.hpp"
	"src/Base/Layer.cpp"
	"src/Base/Layer.hpp"
	"src/Base/Delegate.hpp"
	"src/Base/EventBroadcaster.hpp"
	"src/Component/Transform.hpp"
	"src/Component/PlayerInput.hpp"
	"src/Component/Animation.hpp"
	"src/System/System.hpp"
	"src/System/PlayerInputSystem.hpp"
)

add_executable(test ${SOURCE_LIST})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})
find_package(EnTT CONFIG REQUIRED)

if(EnTT_FOUND)
	target_link_libraries(test PUBLIC EnTT::EnTT)
else()
	message(FATAL_ERROR "EnTT not found")
endif()

message("SDL2_INCLUDE_DIR : ${SDL2_INCLUDE_DIR}")
message("SDL2_LIBRARY_DIR : ${SDL2_LIBRARY_DIR}")

target_include_directories(test
PUBLIC
	${SDL2_INCLUDE_DIR}
)

target_link_libraries(test
PUBLIC
	"${SDL2_LIBRARY_DIR}/SDL2.lib"
	"${SDL2_LIBRARY_DIR}/SDL2main.lib"
	"${SDL2_LIBRARY_DIR}/SDL2_image.lib"
	"${SDL2_LIBRARY_DIR}/SDL2_ttf.lib"
)