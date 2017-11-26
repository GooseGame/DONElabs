add_executable(1 main.cpp)

target_include_directories(1 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(1 PUBLIC cxx_std_17)
target_compile_definitions(1 PRIVATE SFML_STATIC)

target_link_libraries(1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})