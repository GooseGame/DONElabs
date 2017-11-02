add_executable(1d main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(1d PUBLIC cxx_std_17)
target_compile_definitions(1d PRIVATE SFML_STATIC)

target_link_libraries(1d ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})