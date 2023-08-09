cmake_minimum_required(VERSION 3.5)

project(Klaus3D LANGUAGES C)

add_executable(Klaus3D main.c
    disk.h disk.c
    palette.h palette.c
    globals.h)


include(GNUInstallDirs)

if(APPLE)
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
# target_link_libraries(Klaus3D ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
    target_link_libraries(Klaus3D PRIVATE "-framework OpenGL" "-framework GLUT")
endif()

install(TARGETS Klaus3D
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
