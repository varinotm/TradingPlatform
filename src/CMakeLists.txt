# Macro GET_PACKAGE_NAME
#
# Find the relative path of a file
MACRO (GET_PACKAGE_NAME FILE_RELATIVE_PATH PACKAGE_NAME)
   STRING(REGEX MATCH "[/]" HAS_PACKAGE ${FILE})
   IF(HAS_PACKAGE)
      GET_FILENAME_COMPONENT(FILENAME ${FILE} NAME)
      STRING(LENGTH ${FILENAME} FILENAME_LENGTH)
      STRING(LENGTH ${FILE} FILE_LENGTH)
      MATH(EXPR START_FILENAME "${FILE_LENGTH} - ${FILENAME_LENGTH} - 1")
      STRING(SUBSTRING ${FILE} 0 ${START_FILENAME} PATH_TO_FILE)
      STRING(REGEX REPLACE "[/]" "\\\\" PACKAGE_NAME ${PATH_TO_FILE})
   ELSE()
      SET(PACKAGE_NAME -NOTFOUND)
   ENDIF()
ENDMACRO()

# Find the group type of a file using its extension
MACRO (FIND_GROUP_TYPE FILE_RELATIVE_PATH GROUP_TYPE)
   # Get file name from path
   GET_FILENAME_COMPONENT(FILENAME ${FILE_RELATIVE_PATH} NAME)
   STRING(TOLOWER ${FILENAME} FILENAME_LOWER)
   # Get shortest file extension
   STRING(REGEX MATCH "\\.[^.]*$" FILE_EXTENSION ${FILE_RELATIVE_PATH})
 
   # Header files
   IF("${FILE_EXTENSION}" STREQUAL "")
      SET(GROUP_TYPE -NOTFOUND)
   ELSEIF(${FILE_EXTENSION} STREQUAL ".h" OR 
          ${FILE_EXTENSION} STREQUAL ".hh" OR 
          ${FILE_EXTENSION} STREQUAL ".hpp")
      SET(GROUP_TYPE "Header Files")
   # Source files
   ELSEIF(${FILE_EXTENSION} STREQUAL ".c" OR
          ${FILE_EXTENSION} STREQUAL ".cc" OR
          ${FILE_EXTENSION} STREQUAL ".cpp")
      SET(GROUP_TYPE "Source Files")
   # Configuration files
   ELSEIF(${FILE_EXTENSION} STREQUAL ".cmake")
      SET(GROUP_TYPE "Configuration Files")
   ELSEIF(${FILE_EXTENSION} STREQUAL ".qrc")        
      SET(GROUP_TYPE "Qt Resources Files")
   ELSEIF(${FILE_EXTENSION} STREQUAL ".qml" OR
          ${FILE_EXTENSION} STREQUAL ".qmlproject")
      SET(GROUP_TYPE "Qt Files")
   # Resource File
   ELSEIF(${FILE_EXTENSION} STREQUAL ".ico" OR          
          ${FILE_EXTENSION} STREQUAL ".gif" OR
          ${FILE_EXTENSION} STREQUAL ".bmp" OR
          ${FILE_EXTENSION} STREQUAL ".png" OR
          ${FILE_EXTENSION} STREQUAL ".jpg" OR          
          ${FILE_EXTENSION} STREQUAL ".json" OR
          ${FILE_EXTENSION} STREQUAL ".conf" OR
          ${FILE_EXTENSION} STREQUAL ".xml" OR 
          ${FILE_EXTENSION} STREQUAL ".csv" OR
          ${FILE_EXTENSION} STREQUAL ".idx1-ubyte" OR
          ${FILE_EXTENSION} STREQUAL ".idx3-ubyte" OR
          ${FILE_EXTENSION} STREQUAL ".txt")
      SET(GROUP_TYPE "Resources Files")
   # Scripts
   ELSEIF(${FILE_EXTENSION} STREQUAL ".py" OR
          ${FILE_EXTENSION} STREQUAL ".bat")
      SET(GROUP_TYPE "Script Files")
   # Ignore unknown extensions
   ELSE()
      SET(GROUP_TYPE -NOTFOUND)
   ENDIF()
ENDMACRO()

MACRO (AUTO_ADD_SOURCE_FILE FOLDER_PATH FILELIST_VAR)
   FILE(GLOB_RECURSE FILES RELATIVE "${FOLDER_PATH}" "${FOLDER_PATH}/*")
   SET(${FILELIST_VAR})
   # Add known files to the project
   FOREACH(FILE ${FILES})
      # Get package name
      GET_PACKAGE_NAME(${FILE} PACKAGE_NAME)
      # Set the root group name
      FIND_GROUP_TYPE(${FILE} GROUP_TYPE)      
      # Add only file with known extensions
      IF(NOT GROUP_TYPE STREQUAL "-NOTFOUND")
         SET(FILE_ABSOLUTE_PATH "${FOLDER_PATH}/${FILE}")
         SET(GROUP_NAME ${GROUP_TYPE})
         IF(NOT PACKAGE_NAME STREQUAL "-NOTFOUND")     
            SOURCE_GROUP("${GROUP_NAME}\\${PACKAGE_NAME}" FILES ${FILE_ABSOLUTE_PATH})
         ELSE()
            SOURCE_GROUP("${GROUP_NAME}" FILES ${FILE_ABSOLUTE_PATH})
         ENDIF()
         LIST(APPEND ${FILELIST_VAR} "${FILE_ABSOLUTE_PATH}")
      ENDIF()
   ENDFOREACH()
ENDMACRO()

set (C_MAKE_C_FLAGS "-Wall -g")

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

AUTO_ADD_SOURCE_FILE("${CMAKE_CURRENT_SOURCE_DIR}" ALL_EXECUTABLE_FILES_ADDED)

# Create the static library   
ADD_LIBRARY(${PROJECT_NAME}_staticLib STATIC 
            ${ALL_EXECUTABLE_FILES_ADDED})
            
target_compile_definitions(${PROJECT_NAME}_staticLib PRIVATE 
                           $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}_staticLib PRIVATE Qt5::Core Qt5::Quick)

target_include_directories(${PROJECT_NAME}_staticLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
