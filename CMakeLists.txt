cmake_minimum_required(VERSION 3.28)
project(Ramus LANGUAGES CXX)

# =================================================================================================
# Project Settings
# =================================================================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# =================================================================================================
# Dependencies
# =================================================================================================
include(FetchContent)

# CATCH2 OPTIONS
set(CATCH_INSTALL_HELPERS OFF CACHE BOOL "" FORCE)
set(CATCH_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(CATCH_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# GLFW Options
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# spdlog Options
set(SPDLOG_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git   GIT_TAG v3.12.0)
FetchContent_Declare(glm    GIT_REPOSITORY https://github.com/g-truc/glm.git        GIT_TAG 1.0.3)
FetchContent_Declare(glfw   GIT_REPOSITORY https://github.com/glfw/glfw.git         GIT_TAG 3.4)
FetchContent_Declare(imgui  GIT_REPOSITORY https://github.com/ocornut/imgui.git     GIT_TAG v1.92.5)
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git     GIT_TAG v1.17.0)

FetchContent_MakeAvailable(Catch2 glm glfw imgui spdlog)

# =================================================================================================
# ImGui Target
# =================================================================================================
set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui_setup STATIC ${IMGUI_SOURCES})
target_link_libraries(imgui_setup PUBLIC glfw)
target_include_directories(imgui_setup PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)

# =================================================================================================
# Ramus Target
# =================================================================================================
set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    glm::glm 
    glfw 
    spdlog::spdlog
    imgui_setup
)