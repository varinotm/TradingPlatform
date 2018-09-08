#Author : Mathias Varinot
#Date : 25 February 2018

# Activate C++
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




# Minimum required cmake version
cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME "TradingPlatform")

# Defining the project name
project(${PROJECT_NAME})



# Add subdirectory to the project : The CMakeLists.txt file in that subdirectory
# will be used to set up the project
 add_subdirectory(exe)
 add_subdirectory(src)