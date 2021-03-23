cmake_minimum_required(VERSION 2.8)

file(GLOB nenomap
     "*.h"
     "*.cpp"
)

add_executable(nenomap ${nenomap})