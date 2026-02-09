cmake_minimum_required(VERSION 3.28)
project(Ramus LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =================================================================================================
# Project Settings
# =================================================================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# =================================================================================================
# External Dependencies (Auto)
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

set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

set(SPDLOG_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(assimp GIT_REPOSITORY https://github.com/assimp/assimp.git     GIT_TAG v6.0.4)
FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git   GIT_TAG v3.12.0)
FetchContent_Declare(glm    GIT_REPOSITORY https://github.com/g-truc/glm.git        GIT_TAG 1.0.3)
FetchContent_Declare(glfw   GIT_REPOSITORY https://github.com/glfw/glfw.git         GIT_TAG 3.4)
FetchContent_Declare(imgui  GIT_REPOSITORY https://github.com/ocornut/imgui.git     GIT_TAG v1.92.5)
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git     GIT_TAG v1.17.0)

FetchContent_MakeAvailable(assimp Catch2 glm glfw imgui spdlog)

# =================================================================================================
# External Dependencies (Manual)
# =================================================================================================
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/gl.c")
set(GLAD_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include")

add_library(glad STATIC ${GLAD_SOURCE})

target_include_directories(glad PUBLIC ${GLAD_INCLUDE})

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
target_link_libraries(imgui_setup PUBLIC glfw glad)
target_include_directories(imgui_setup PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)

# =================================================================================================
# Ramus Library
# =================================================================================================
add_library(RamusEngine STATIC
    src/Core/App.cpp
    src/Core/Window.cpp
    src/Core/Log.cpp
    src/Core/ServiceLocator.cpp
    src/Graphics/Model.cpp
    src/Graphics/Material.cpp
    src/Graphics/Mesh.cpp
    src/Graphics/Renderer.cpp
    src/Graphics/Shader.cpp
    src/Graphics/Texture.cpp
    src/Graphics/Vertex.cpp
    src/Graphics/RHI/Buffer.cpp
    src/Graphics/RHI/GraphicsContext.cpp
    src/Graphics/RHI/GraphicsDevice.cpp
    src/Graphics/RHI/VertexArray.cpp
    src/Resources/ResourceService.cpp
    src/Resources/ModelLoader.cpp
    src/Resources/ShaderLoader.cpp
    src/Resources/TextureLoader.cpp
)

target_include_directories(RamusEngine 
    PUBLIC 
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        include/Ramus/Graphics/RHI
    PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(RamusEngine 
    PUBLIC
        glm::glm
        spdlog::spdlog
        glad
    PRIVATE
        assimp::assimp
        glfw
)

# =================================================================================================
# Ramus Greenhouse (Demo App)
# =================================================================================================
add_executable(RamusGreenhouse greenhouse/main.cpp)

target_link_libraries(RamusGreenhouse PRIVATE
    RamusEngine
    imgui_setup
)

# =================================================================================================
# Ramus Greenhouse Post-Build
# =================================================================================================
set(ASSETS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")

add_custom_command(
    TARGET RamusGreenhouse POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSETS_SOURCE_DIR}"
        "$<TARGET_FILE_DIR:RamusGreenhouse>/assets"
    COMMENT "Copying assets to build directory..."
)