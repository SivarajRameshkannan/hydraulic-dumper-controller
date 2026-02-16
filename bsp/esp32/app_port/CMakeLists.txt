idf_component_register(
    SRCS
    INCLUDE_DIRS "."
)

# Link portable lib into this component
target_link_libraries(${COMPONENT_LIB} INTERFACE core_app)

# Add your portable library
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../
    ${CMAKE_BINARY_DIR}/portable_lib_build
)

# Tell portable code it's ESP32
#target_compile_definitions(core_app PUBLIC HAL_ESP32)


