add_executable(${APP_EXE} main.cpp "UI/Window.h" "UI/Window.cpp" "UI/Canvas.h" "UI/Canvas.cpp" "UI/UIBar.h" "UI/UIBar.cpp" "UI/ShapeSelector.h" "UI/ShapeSelector.cpp" "Utils/Saver.h" "Utils/Saver.cpp" "Objects/Object.cpp" "Objects/Object.h" "Controllers/Controller.cpp" "Objects/Line.cpp" "Controllers/ObjectsFactory.h" "Objects/Rectangle.h" "Objects/Rectangle.cpp" "Objects/Ellipse.cpp" "Objects/Triangle.h" "Objects/Triangle.cpp" "Utils/Config.h" "UI/ColorSelector.h" "UI/ColorSelector.cpp" "UI/LineSelector.h" "UI/LineSelector.cpp" "UI/ToolSelector.h" "UI/ToolSelector.cpp" "UI/FileTool.h" "UI/FileTool.cpp")

target_include_directories(${APP_EXE} PRIVATE .)

target_link_libraries(${APP_EXE} PRIVATE tgui)
target_link_libraries(${APP_EXE} PRIVATE sfml-system sfml-window sfml-graphics)

set(SOURCE_RESOURCES_DIR "${PROJECT_SOURCE_DIR}/src/images")
set(DEST_RESOURCES_DIR "${CMAKE_BINARY_DIR}/src/images")
# Copy the resources to the build directory
add_custom_command(
  TARGET ${APP_EXE} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_RESOURCES_DIR} ${DEST_RESOURCES_DIR}
  COMMENT "Copying resources to build directory"
) 