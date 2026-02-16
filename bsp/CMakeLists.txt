set(BOARD esp32)
add_library(bsp INTERFACE)
target_link_libraries(bsp INTERFACE ${BOARD})

add_subdirectory(${BOARD})

target_link_libraries(bsp INTERFACE services)