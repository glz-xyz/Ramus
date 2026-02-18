cmake_minimum_required(VERSION 3.28)
project(Ramus LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =================================================================================================
# Project Settings
# =================================================================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Build/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Build/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Build/lib")

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
FetchContent_Declare(json   GIT_REPOSITORY https://github.com/nlohmann/json.git     GIT_TAG v3.12.0)
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git     GIT_TAG v1.17.0)
FetchContent_Declare(stb    GIT_REPOSITORY https://github.com/nothings/stb.git      master)

FetchContent_MakeAvailable(assimp Catch2 glm glfw imgui json spdlog)

# Note: stb has no CMakeLists.txt
FetchContent_GetProperties(stb)
if(NOT stb_POPULATED)
    FetchContent_Populate(stb)
    
    add_library(stb INTERFACE)
    target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})
endif()

# =================================================================================================
# External Dependencies (Manual)
# =================================================================================================
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glad/src/gl.c")
set(GLAD_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glad/include")

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
    Source/src/Core/Engine/Engine.cpp
    Source/src/Core/Engine/Input.cpp
    Source/src/Core/Engine/Window.cpp
    Source/src/Core/Services/Logger.cpp
    Source/src/Assets/Asset.cpp
    Source/src/Assets/AssetManager.cpp
    Source/src/Assets/Material.cpp
    Source/src/Assets/Model.cpp
    Source/src/Assets/Texture.cpp
    Source/src/Assets/Loaders/MaterialLoader.cpp
    Source/src/Assets/Loaders/ModelLoader.cpp
    Source/src/Assets/Loaders/TextureLoader.cpp
    Source/src/Graphics/Renderer/Renderer.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLBuffer.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLContext.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLDevice.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLIndexBuffer.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLMesh.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLResource.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLShader.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLShaderProgram.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLStorageBuffer.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLTexture.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLUniformBuffer.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLVertexArray.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLVertexBuffer.cpp
    Source/src/Graphics/Device/OpenGL/OpenGLUtils.cpp
    Source/src/Graphics/Geometry/Mesh.cpp
)

target_include_directories(RamusEngine 
    PUBLIC 
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/include"
    PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/src"
)

target_link_libraries(RamusEngine 
    PUBLIC
        glm::glm
        spdlog::spdlog
        glad
        nlohmann_json::nlohmann_json
    PRIVATE
        assimp::assimp
        glfw
        stb
)

# =================================================================================================
# Ramus Greenhouse (Demo App)
# =================================================================================================
add_executable(RamusGreenhouse 
    "${CMAKE_SOURCE_DIR}/Source/src/Core/Engine/EngineMain.cpp"
    "${CMAKE_SOURCE_DIR}/Samples/Greenhouse/GreenhouseApp.cpp")

target_link_libraries(RamusGreenhouse PRIVATE
    RamusEngine
    imgui_setup
)

# =================================================================================================
# Ramus Greenhouse Post-Build
# =================================================================================================
add_custom_command(
    TARGET RamusGreenhouse POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:RamusGreenhouse>/Assets" #[TODO] Assets/Engine/
    COMMENT "Deploying Ramus Engine assets..."
)

add_custom_command(
    TARGET RamusGreenhouse POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Samples/Greenhouse/Assets"
        "$<TARGET_FILE_DIR:RamusGreenhouse>/Assets" #[TODO] Assets/App/
    COMMENT "Deploying Greenhouse app assets..."
)