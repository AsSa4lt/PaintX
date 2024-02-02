add_executable(${APP_EXE} main.cpp "UI/Window.h" "UI/Window.cpp" "UI/Canvas.h" "UI/Canvas.cpp" "UI/UIBar.h" "UI/UIBar.cpp" "UI/ShapeSelector.h" "UI/ShapeSelector.cpp" "Utils/Saver.h" "Utils/Saver.cpp" "Objects/Object.cpp" "Objects/Object.h" "Controllers/Controller.cpp" "Objects/Line.cpp" "Controllers/ObjectsFactory.h")

target_include_directories(${APP_EXE} PRIVATE .)

target_link_libraries(${APP_EXE} PRIVATE tgui)
target_link_libraries(${APP_EXE} PRIVATE sfml-system sfml-window sfml-graphics)