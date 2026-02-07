cmake_minimum_required(VERSION 3.28)
project(Ramus LANGUAGES CXX C)

# =================================================================================================
# Project Settings
# =================================================================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# =================================================================================================
# External Dependencies
# =================================================================================================
include(FetchContent)

set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)

set(CATCH_INSTALL_HELPERS OFF CACHE BOOL "" FORCE)
set(CATCH_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(CATCH_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(GLAD_GL_VERSION "4.6" CACHE STRING "" FORCE)
set(GLAD_GL_PROFILE "Core" CACHE STRING "" FORCE)
set(GLAD_INSTALL OFF CACHE BOOL "" FORCE)

set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

set(SPDLOG_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(assimp GIT_REPOSITORY https://github.com/assimp/assimp.git     GIT_TAG v6.0.4)
FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git   GIT_TAG v3.12.0)
FetchContent_Declare(glad   GIT_REPOSITORY https://github.com/Dav1dde/glad.git      GIT_TAG v2.0.8  GIT_PROGRESS TRUE SOURCE_SUBDIR cmake)
FetchContent_Declare(glm    GIT_REPOSITORY https://github.com/g-truc/glm.git        GIT_TAG 1.0.3)
FetchContent_Declare(glfw   GIT_REPOSITORY https://github.com/glfw/glfw.git         GIT_TAG 3.4)
FetchContent_Declare(imgui  GIT_REPOSITORY https://github.com/ocornut/imgui.git     GIT_TAG v1.92.5)
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git     GIT_TAG v1.17.0)

FetchContent_MakeAvailable(assimp Catch2 glad glm glfw imgui spdlog)

glad_add_library(glad_gl_core_46 STATIC REPRODUCIBLE LOADER API gl:core=4.6)

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
# Ramus Library
# =================================================================================================
add_library(RamusEngine STATIC
    src/Core/App.cpp
    src/Core/Window.cpp
    src/Core/Log.cpp
    src/Core/ServiceLocator.cpp
    src/Resources/ResourceService.cpp
    src/Graphics/GraphicsContext.cpp
    src/Graphics/GraphicsDevice.cpp
    src/Graphics/Renderer.cpp
    src/Graphics/Model.cpp
    src/Graphics/Material.cpp
    src/Graphics/Mesh.cpp
    src/Graphics/Vertex.cpp
)

target_include_directories(RamusEngine 
    PUBLIC include
    PRIVATE src
)

target_link_libraries(RamusEngine 
    PUBLIC
        glm::glm
        spdlog::spdlog
    PRIVATE
        assimp::assimp
        glfw
        glad_gl_core_46
)

# =================================================================================================
# Ramus Demo/Test Target
# =================================================================================================
add_executable(RamusGreenhouse greenhouse/main.cpp)

target_link_libraries(RamusGreenhouse PRIVATE
    RamusEngine
    imgui_setup
)

