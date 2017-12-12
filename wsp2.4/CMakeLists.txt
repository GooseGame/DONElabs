add_executable(samodelochka main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

target_include_directories(samodelochka PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(samodelochka PUBLIC cxx_std_17)
target_compile_definitions(samodelochka PRIVATE SFML_STATIC)

target_link_libraries(samodelochka ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})