CMAKE_MINIMUM_REQUIRED( VERSION 3.10 )
PROJECT( Morfeus VERSION 0.1 DESCRIPTION "GUI application launcher for Linux with history" )

# The project settings
SET( BIN_NAME "morfeus" )                   # Executable binnary filename
SET( CMAKE_INSTALL_PREFIX "/usr" )          # Install target directory
SET( LIB_FOX   "/opt/foxlib/1.7/81" )       # Fox toolkit path
SET( LIB_FXGHI "/opt/foxghi/0.4/1"  )       # Fox GHI path
SET( CMAKE_CXX_STANDARD 11 )                # C++ Standard
SET( CMAKE_CXX_STANDARD_REQUIRED True )     # C++ Standard
#add_compile_options(-Wall -Wextra -pedantic -Werror)
#add_compile_options(-Wall -pedantic)

# Configure project
#CONFIGURE_FILE( MakeConfig.h.in MakeConfig.h )
FILE( GLOB SOURCES src/*.cpp )                          # List of implementation files
INCLUDE_DIRECTORIES( "${PROJECT_SOURCE_DIR}/include" )

# Add directories for project dependecies
INCLUDE_DIRECTORIES( "${LIB_FOX}/include/" )
LINK_DIRECTORIES(    "${LIB_FOX}/lib/" )
INCLUDE_DIRECTORIES( "${LIB_FXGHI}/include/" )
LINK_DIRECTORIES(    "${LIB_FXGHI}/lib/" )

# Add to the executable
ADD_EXECUTABLE( ${BIN_NAME} ${SOURCES} )
TARGET_LINK_LIBRARIES( ${BIN_NAME} FOX-1.7 FXGHI tinyxml2 )
#TARGET_INCLUDE_DIRECTORIES( Morfeus PUBLIC "${PROJECT_BINARY_DIR}" )

# Install build project
INSTALL( TARGETS ${BIN_NAME} RUNTIME DESTINATION bin )
INSTALL( DIRECTORY data DESTINATION ${CMAKE_INSTALL_PREFIX}/share/games/morfeus )		# Globalni data
#INSTALL( FILES integration/${PROJECT_NAME}.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pixmaps/ )
#INSTALL( FILES integration/${PROJECT_NAME}.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications/ )


### END ###
