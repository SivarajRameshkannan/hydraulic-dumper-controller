add_library(mock INTERFACE)

target_include_directories(mock INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#add dependancy
target_link_libraries(mock INTERFACE hal)