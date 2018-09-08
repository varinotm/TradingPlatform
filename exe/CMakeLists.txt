# Define target application executable and the list of source and header files
add_executable(${PROJECT_NAME} main.cpp)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_staticLib Qt5::Core Qt5::Quick)