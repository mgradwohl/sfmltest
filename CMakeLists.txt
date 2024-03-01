cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(GSL
    GIT_REPOSITORY https://github.com/microsoft/GSL.git
    GIT_TAG main
    GIT_SHALLOW ON)
FetchContent_MakeAvailable(GSL)

add_executable(CMakeSFMLProject src/main.cpp src/Renderer.cpp src/Cell.cpp src/Board.cpp)
target_include_directories(CMakeSFMLProject PRIVATE "${PROJECT_SOURCE_DIR}/include/build/_deps/gsl-src/include")
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_link_libraries(CMakeSFMLProject PRIVATE Microsoft.GSL::GSL)

target_compile_features(CMakeSFMLProject PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

install(TARGETS CMakeSFMLProject)