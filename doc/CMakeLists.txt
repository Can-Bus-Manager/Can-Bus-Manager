# doc/CMakeLists.txt

find_package(Doxygen)

if(DOXYGEN_FOUND)
    # 1. Define where the output should go (relative to the project root)
    set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/doc")

    # 2. Configure the Doxyfile.in
    # This reads doc/Doxyfile.in and writes it to the build folder
    configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
            ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            @ONLY
    )

    # 3. Create the 'docs' build target
    add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
    )

    message(STATUS "Doxygen target 'docs' added.")
else()
    message(WARNING "Doxygen not found. 'docs' target will not be available.")
endif()