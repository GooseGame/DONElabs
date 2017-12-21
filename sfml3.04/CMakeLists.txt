add_executable(sfml3.04 main.cpp)

target_include_directories(sfml3.04 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml3.04 PUBLIC cxx_std_17)
target_compile_definitions(sfml3.04 PRIVATE SFML_STATIC)

target_link_libraries(sfml3.04 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})