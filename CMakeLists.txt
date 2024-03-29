cmake_minimum_required (VERSION 3.9)

project(Engine VERSION 1.0.1 DESCRIPTION "Engine description")


SET (CMAKE_C_FLAGS_INIT                "-Wall")
SET (CMAKE_C_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

SET (CMAKE_CXX_FLAGS_INIT                "-Wall")
SET (CMAKE_CXX_STANDARD                   17)
SET (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")


SET(ENGINE_SRCS_PATH     "${PROJECT_SOURCE_DIR}/Engine/src")
SET(SPDLOG_INCLUDE_PATH  "${PROJECT_SOURCE_DIR}/Engine/vendor/spdlog/include")
SET(GLFW_INCLUDE_PATH    "${PROJECT_SOURCE_DIR}/Engine/vendor/glfw/GLFW/include")
SET(GLAD_INCLUDE_PATH    "${PROJECT_SOURCE_DIR}/Engine/vendor/Glad/include")
SET(IMGUI_INCLUDE_PATH   "${PROJECT_SOURCE_DIR}/Engine/vendor/imgui/ImGui")
SET(GLM_INCLUDE_PATH     "${PROJECT_SOURCE_DIR}/Engine/vendor/glm")
SET(STB_IMAGE_INCLUDE_PATH     "${PROJECT_SOURCE_DIR}/Engine/vendor/stb_image")

add_subdirectory(${PROJECT_SOURCE_DIR}/Engine/vendor/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/Engine/vendor/Glad)
add_subdirectory(${PROJECT_SOURCE_DIR}/Engine/vendor/imgui)

add_compile_definitions(GLFW_INCLUDE_NONE)

FILE(GLOB_RECURSE ENGINE_SRCS "${ENGINE_SRCS_PATH}/*.cpp" "${PROJECT_SOURCE_DIR}/Engine/vendor/stb_image/*.cpp", "${PROJECT_SOURCE_DIR}/Engine/vendor/stb_image/*.h")

ADD_LIBRARY(Engine STATIC ${ENGINE_SRCS} $<TARGET_OBJECTS:GLFW> 
                                         $<TARGET_OBJECTS:Glad>
                                         $<TARGET_OBJECTS:ImGui>)

set_target_properties(Engine PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/Engine)

target_include_directories(Engine PUBLIC ${ENGINE_SRCS_PATH} 
                                         ${SPDLOG_INCLUDE_PATH}
                                         ${GLFW_INCLUDE_PATH}
                                         ${GLAD_INCLUDE_PATH}
                                         ${IMGUI_INCLUDE_PATH}
                                         ${GLM_INCLUDE_PATH}
                                         ${STB_IMAGE_INCLUDE_PATH})

target_link_libraries(Engine PUBLIC pthread dl)

set(SANDBOX_SRCS_PATH  "${PROJECT_SOURCE_DIR}/Sandbox/src")
file(GLOB_RECURSE SANDBOX_SRCS "${SANDBOX_SRCS_PATH}/*.cpp" "${SANDBOX_SRCS_PATH}/*.h")

add_executable(Sandbox ${SANDBOX_SRCS})

set_target_properties(Sandbox PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/Sandbox)
target_include_directories(Sandbox PUBLIC ${ENGINE_SRCS_PATH})
target_link_libraries(Sandbox PUBLIC Engine)

set_target_properties(Sandbox PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/Sandbox)


set(TEST_SRCS_PATH  "${PROJECT_SOURCE_DIR}/Test/")
file(GLOB_RECURSE TEST_SRCS "${TEST_SRCS_PATH}/TextureTest.cpp")

add_executable(Test ${TEST_SRCS})

set_target_properties(Test PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/Test)
target_include_directories(Test PUBLIC ${ENGINE_SRCS_PATH})
target_link_libraries(Test PUBLIC Engine)

set_target_properties(Test PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/Test)
