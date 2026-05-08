# CMakeLists.txt
cmake_minimum_required(VERSION 3.21)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Snowboard")

list(APPEND CMAKE_PREFIX_PATH
    "${CMAKE_SOURCE_DIR}/libs/SDL3-devel-3.4.6-VC"
)

set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/libs/imgui")

find_package(SDL3       REQUIRED CONFIG)

set(IMGUI_SOURCES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"

    "${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp"
)

add_executable(Snowboard 
    "src/Main.cpp" 
    "src/audioSystem.cpp" 
    "src/audioSystem.h" 
    "src/renderer.cpp" 
    "src/renderer.h"
    "src/audioManager.h"
    "src/audioManager.cpp"
    "src/interface.h"
    "src/interface.cpp"

    "libs/miniaudio.h"
    ${IMGUI_SOURCES}
)

set_property(TARGET Snowboard PROPERTY CXX_STANDARD 20)

target_include_directories(Snowboard PRIVATE 
    "${CMAKE_SOURCE_DIR}/libs/"
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends" 
)

target_link_libraries(Snowboard PRIVATE
    SDL3::SDL3
)

# dont mind ts
add_custom_command(TARGET Snowboard POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resources"
    "$<TARGET_FILE_DIR:Snowboard>/resources"
)

install(TARGETS Snowboard DESTINATION .)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/resources/" DESTINATION "resources")

if(WIN32)
    add_custom_command(TARGET Snowboard POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:Snowboard>
            $<TARGET_FILE_DIR:Snowboard>
        COMMAND_EXPAND_LISTS
        COMMENT "Copying SDL3 DLLs"
    )
endif()