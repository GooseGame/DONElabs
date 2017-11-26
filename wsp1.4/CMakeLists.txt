add_executable(samosamodelochka main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

target_include_directories(samosamodelochka PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(samosamodelochka PUBLIC cxx_std_17)
target_compile_definitions(samosamodelochka PRIVATE SFML_STATIC)

target_link_libraries(samosamodelochka ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})