cmake_minimum_required(VERSION 3.14.0)
project(karaoke-midipp VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
# add_compile_options("-std=c++17")
# add_compile_options("-std=c++17")
include(CTest)
enable_testing()
find_package(Boost 1.70 REQUIRED COMPONENTS filesystem exception date_time  system program_options PATHS ~/.local)
set(JANSSON_LIBRARIES -ljansson)
find_path(JANSSON_INCLUDE_DIR NAMES jansson.h)

add_subdirectory(ext/midifile)

set(CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG")
set(SRC lyrics.h lyrics.cpp
lyrics_event.h lyrics_event.cpp
lyrics_serializer.h lyrics_serializer.cpp
lyrics_extractor.h lyrics_extractor.cpp)

include_directories(ext/midifile/include ${JANSSON_INCLUDE_DIR})

add_executable(karaoke-midipp main.cpp ${SRC})

add_dependencies(karaoke-midipp midifile Boost::headers Boost::filesystem  Boost::system Boost::date_time Boost::program_options)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(karaoke-midipp ${JANSSON_LIBRARIES} Boost::headers Boost::system Boost::filesystem Boost::date_time Boost::program_options midifile)
message({Boost::headers})