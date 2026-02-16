# Collect all source files recursively
file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Create the services library
add_library(services ${SRCS})

# Include current directory for headers
target_include_directories(services PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link services library to hal library
target_link_libraries(services PUBLIC bsp hal devices utils)

