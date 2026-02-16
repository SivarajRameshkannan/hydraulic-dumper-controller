file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(esp32 ${SRCS})

target_include_directories(esp32 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(esp32
      PUBLIC
      idf::freertos
      idf::driver
      idf::esp_system
      idf::esp_timer

      hal
)