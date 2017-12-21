add_executable(31 main.cpp)

target_include_directories(31 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(31 PUBLIC cxx_std_17)
target_compile_definitions(31 PRIVATE SFML_STATIC)

target_link_libraries(31 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})