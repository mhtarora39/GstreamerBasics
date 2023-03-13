cmake_minimum_required(VERSION 3.16)

project(rtsp_client) #Project name

set(CMAKE_CXX_STANDARD 14) #setting C++ 14 standard
find_package(PkgConfig) #finding pkg-config is a helper tool
find_package( OpenCV REQUIRED )
#include_directories( ${OpenCV_INCLUDE_DIRS} )

#using pkg-config to getting Gstreamer
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

#including GStreamer header files directory
include_directories(
        ${GLIB_INCLUDE_DIRS}
        ${GSTREAMER_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
message(${OpenCV_INCLUDE_DIRS})
#linking GStreamer library directory
link_directories(
        ${GLIB_LIBRARY_DIRS}
        ${GSTREAMER_LIBRARY_DIRS}
)

#building target executable
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
                               ${CMAKE_CURRENT_SOURCE_DIR}/src/rtsp_client.cpp
                               ${CMAKE_CURRENT_SOURCE_DIR}/src/rtsp_worker.cpp)


ADD_LIBRARY(gstbackgroundsub SHARED
           ${CMAKE_CURRENT_SOURCE_DIR}/src/plugins/gstbackgroundsub.cpp)

target_link_libraries(gstbackgroundsub ${GSTREAMER_LIBRARIES} ${OpenCV_LIBS} gstapp-1.0 gstvideo-1.0)
   
#linking Gstreamer library with target executable
target_link_libraries(${PROJECT_NAME} ${GSTREAMER_LIBRARIES} ${OpenCV_LIBS} gstapp-1.0 gstvideo-1.0)




