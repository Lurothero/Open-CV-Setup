cmake_minimum_required(VERSION 3.10)

project(Apple) #CMAKE TEMPLATE


#OPENCV
set(OpenCV_DIR C:/opencv/build)
find_package(OpenCV REQUIRED)


# Locate and include SDL2
set(SDL2_DIR C:/SDL2/cmake)
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${SDL2_LIBRARIES})