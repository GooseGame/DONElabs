<<<<<<< HEAD
add_executable(203 main.cpp)
=======
add_executable(203 main.cpp)
>>>>>>> bb027917d545a94f2cbb720201d034ee6cd16cd8

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

<<<<<<< HEAD
target_include_directories(203 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(203 PUBLIC cxx_std_17)
target_compile_definitions(203 PRIVATE SFML_STATIC)

target_link_libraries(203 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
=======
target_include_directories(203 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(203 PUBLIC cxx_std_17)
target_compile_definitions(203 PRIVATE SFML_STATIC)

target_link_libraries(203 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
>>>>>>> bb027917d545a94f2cbb720201d034ee6cd16cd8
