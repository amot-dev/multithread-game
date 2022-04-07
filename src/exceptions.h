#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <exception>
#include <string>

class TileMissingException : public std::exception {
   const char* what() const noexcept override {return "Error: Tile in view distance is missing!";};
};

class InvalidBiomeFound : public std::exception {
   const char* what() const noexcept override {return "Error: This world contains a biome that doesn't exist!";};
};

class InvalidFeatureFound : public std::exception {
   const char* what() const noexcept override {return "Error: This world contains a feature that doesn't exist!";};
};

class InvalidBoardLoad : public std::exception {
   const char* what() const noexcept override {return "Error: This world is not correctly generated!";};
};

#endif