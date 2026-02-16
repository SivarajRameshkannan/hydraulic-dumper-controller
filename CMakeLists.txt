file(GLOB  SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(core_app STATIC
    ${SRC}
)

target_include_directories(core_app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

#add dependancy
target_link_libraries(core_app
    PRIVATE hal services interfaces devices bsp
)

add_subdirectory(devices)
add_subdirectory(services)
add_subdirectory(interfaces)
add_subdirectory(hal)
add_subdirectory(bsp)
add_subdirectory(utils)