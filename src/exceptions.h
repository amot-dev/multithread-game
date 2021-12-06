#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <exception>
#include <string>

class TileMissingException : public std::exception {
   const char* what() const noexcept override {return "Error: Tile in view distance is missing!";};
};

class InvalidBoardLoad : public std::exception {
   const char* what() const noexcept override {return "Error: This board is not correctly generated!";};
};

#endif