# Target link libraries

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(RType raylib)
target_link_libraries(RType Boost::iostreams)

target_link_libraries(RType ZLIB::ZLIB)