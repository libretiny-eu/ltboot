# Create ltboot-lib for ports to use
add_library(${PROJECT_NAME}-lib INTERFACE)
target_include_directories(${PROJECT_NAME}-lib INTERFACE include)
target_link_libraries(${PROJECT_NAME}-lib INTERFACE git_version)
target_compile_definitions(${PROJECT_NAME}-lib INTERFACE LTB_PORT=${LTB_PORT})

# Find all available ports
file(GLOB PORTS RELATIVE ${CMAKE_CURRENT_LIST_DIR}/port port/*)
# Validate LTB_PORT selection
if (NOT (LTB_PORT IN_LIST PORTS))
	list(JOIN PORTS ", " PORTS_STR)
	message(FATAL_ERROR "Invalid port selected - set LTB_PORT to one of: ${PORTS_STR}")
endif ()

# Add CMakeLists for selected port
add_subdirectory(port/${LTB_PORT})

# Validate LTB_FAMILY selection
if (NOT (LTB_FAMILY IN_LIST PORT_FAMILIES))
	list(JOIN PORT_FAMILIES ", " FAMILIES_STR)
	message(FATAL_ERROR "Invalid family selected - set LTB_FAMILY to one of: ${FAMILIES_STR}")
endif ()
# Convert LTB_FAMILY to uppercase
string(TOUPPER LTB_FAMILY LTB_FAMILY)
# Add LTB_FAMILY for C code
target_compile_definitions(${PROJECT_NAME}-lib INTERFACE LTB_FAMILY=F_${LTB_FAMILY})

# Find main sources
file(GLOB SRCS *.c)

# Add main executable
add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
target_link_libraries(${PROJECT_NAME} -Wl,--whole-archive ${PROJECT_NAME}-port -Wl,--no-whole-archive)

print_section_sizes(${PROJECT_NAME})
print_sections(${PROJECT_NAME})
create_bin_output(${PROJECT_NAME})
