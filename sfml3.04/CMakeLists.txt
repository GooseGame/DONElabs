add_executable(34 main.cpp)

target_include_directories(34 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(34 PUBLIC cxx_std_17)
target_compile_definitions(34 PRIVATE SFML_STATIC)

target_link_libraries(34 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})