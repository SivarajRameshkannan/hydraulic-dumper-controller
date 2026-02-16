file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(devices ${SRC})

target_include_directories(devices PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

#add dependancy
target_link_libraries(devices PRIVATE hal services)