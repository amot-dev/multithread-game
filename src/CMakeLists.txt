add_executable(multithread-game board.cpp interface.cpp main.cpp tile.cpp utility.cpp)
target_link_libraries(multithread-game cereal)