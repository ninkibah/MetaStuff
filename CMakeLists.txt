cmake_minimum_required( VERSION 2.8 )
project( MetaStuff )

option(WITH_EXAMPLES "Build examples" ON)

include(GNUInstallDirs)

# copy the header files
install(
    DIRECTORY include
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}
    ) 

if(WITH_EXAMPLES)
    add_subdirectory(example)
endif(WITH_EXAMPLES)
