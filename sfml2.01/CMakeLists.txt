add_executable(sfml2.01 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

target_include_directories(sfml2.01 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml2.01 PUBLIC cxx_std_17)
target_compile_definitions(sfml2.01 PRIVATE SFML_STATIC)

target_link_libraries(sfml2.01 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})