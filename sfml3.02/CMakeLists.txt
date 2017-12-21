add_executable(302 main.cpp)

target_include_directories(302 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(302 PUBLIC cxx_std_17)
target_compile_definitions(302 PRIVATE SFML_STATIC)

target_link_libraries(302 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})