add_executable(wsp2.3 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

target_include_directories(wsp2.3 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(wsp2.3 PUBLIC cxx_std_17)
target_compile_definitions(wsp2.3 PRIVATE SFML_STATIC)

target_link_libraries(wsp2.3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})