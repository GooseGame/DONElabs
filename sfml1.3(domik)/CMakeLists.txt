add_executable(2d main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(2d PUBLIC cxx_std_17)
target_compile_definitions(2d PRIVATE SFML_STATIC)

target_link_libraries(2d ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})