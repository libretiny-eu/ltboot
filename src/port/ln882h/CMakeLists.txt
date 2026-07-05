set(BUILD_FLAGS -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wno-unused-variable)
set(LINKER_SCRIPT "ln882h.ld")
set(LINKER_SRC "${CMAKE_CURRENT_LIST_DIR}/${LINKER_SCRIPT}s")
set(LINKER_GEN "${CMAKE_CURRENT_BINARY_DIR}/${LINKER_SCRIPT}")
set(PORT_FAMILIES ln882h PARENT_SCOPE)

add_custom_target(
	${LINKER_SCRIPT}
	DEPENDS ${LINKER_SRC}
	COMMAND ${CMAKE_C_COMPILER} -E -P -x c ${LINKER_SRC} -o ${LINKER_SCRIPT} -DLN882H_SRAM=1
)

file(GLOB SRCS *.c)

add_library(${PROJECT_NAME}-port STATIC ${SRCS})
add_dependencies(${PROJECT_NAME}-port ${LINKER_SCRIPT})
target_include_directories(${PROJECT_NAME}-port PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(${PROJECT_NAME}-port PUBLIC ${BUILD_FLAGS})
target_link_options(${PROJECT_NAME}-port PUBLIC ${BUILD_FLAGS} -T${LINKER_GEN})
target_link_libraries(${PROJECT_NAME}-port PRIVATE ${PROJECT_NAME}-lib)
target_link_libraries(${PROJECT_NAME}-port PRIVATE CMSIS_6)
