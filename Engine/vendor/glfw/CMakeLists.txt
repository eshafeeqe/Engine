cmake_minimum_required (VERSION 3.9)

project(GLFW C)

add_compile_definitions(_GLFW_X11)

set(GLFW_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/GLFW")

INCLUDE_DIRECTORIES(${GLFW_SRC_PATH}/src ${GLFW_SRC_PATH}/include)

add_library(GLFW STATIC ${GLFW_SRC_PATH}/include/GLFW/glfw3.h
                        ${GLFW_SRC_PATH}/include/GLFW/glfw3native.h
                        ${GLFW_SRC_PATH}/src/internal.h
                        ${GLFW_SRC_PATH}/src/platform.h
                        ${GLFW_SRC_PATH}/src/mappings.h
                        ${GLFW_SRC_PATH}/src/context.c
                        ${GLFW_SRC_PATH}/src/init.c
                        ${GLFW_SRC_PATH}/src/input.c
                        ${GLFW_SRC_PATH}/src/monitor.c
                        ${GLFW_SRC_PATH}/src/platform.c
                        ${GLFW_SRC_PATH}/src/vulkan.c
                        ${GLFW_SRC_PATH}/src/window.c
                        ${GLFW_SRC_PATH}/src/egl_context.c
                        ${GLFW_SRC_PATH}/src/osmesa_context.c
                        ${GLFW_SRC_PATH}/src/null_platform.h
                        ${GLFW_SRC_PATH}/src/null_joystick.h
                        ${GLFW_SRC_PATH}/src/null_init.c
                        ${GLFW_SRC_PATH}/src/null_monitor.c
                        ${GLFW_SRC_PATH}/src/null_window.c
                        ${GLFW_SRC_PATH}/src/null_joystick.c


                        ${GLFW_SRC_PATH}/src/x11_init.c
                        ${GLFW_SRC_PATH}/src/x11_window.c
                        ${GLFW_SRC_PATH}/src/x11_init.c
                        ${GLFW_SRC_PATH}/src/x11_monitor.c
                        ${GLFW_SRC_PATH}/src/x11_window.c
                        ${GLFW_SRC_PATH}/src/xkb_unicode.c
                        ${GLFW_SRC_PATH}/src/platform.c
                        ${GLFW_SRC_PATH}/src/posix_time.c
                        ${GLFW_SRC_PATH}/src/posix_thread.c
                        ${GLFW_SRC_PATH}/src/posix_module.c
                        ${GLFW_SRC_PATH}/src/glx_context.c
                        ${GLFW_SRC_PATH}/src/egl_context.c
                        ${GLFW_SRC_PATH}/src/osmesa_context.c
                        ${GLFW_SRC_PATH}/src/linux_joystick.c)

set_target_properties(GLFW PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${GLFW_SRC_PATH}/bin/GLFW)

set_property(TARGET GLFW PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(GLFW PUBLIC ${GLFW_SRC_PATH}/include/)


