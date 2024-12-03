set(TARGET_NAME LNLibViewer)
project(${TARGET_NAME} LANGUAGES CXX)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${TARGET_NAME})
target_compile_definitions(${TARGET_NAME}  PRIVATE ${TARGET_NAME}_HOME)

target_include_directories(${TARGET_NAME} PUBLIC
	"${SOURCE_DIR}/include"
	"${VTK_DIR}/include"
	"${LNLib_DIR}/include"
)

file(GLOB VTK_LIB_FILES ${VTK_DIR}/lib/*.lib)
list(APPEND LIBS ${VTK_LIB_FILES})

target_link_libraries(${TARGET_NAME} ${LIBS} ${LNLib_DIR}/lib/$<CONFIG>/LNLib.lib)

file(GLOB rootfiles *.cpp *.h)
source_group("" FILES ${rootfiles})
target_sources(${TARGET_NAME} PRIVATE ${rootfiles})
SUBDIRLIST(SUBDIRS ${SOURCE_DIR})
foreach(subdir ${SUBDIRS})
    file(GLOB subdirFiles ${subdir}/*.cpp ${subdir}/*.h)
    string(REPLACE "/" "\\" subdir ${subdir})
    source_group(${subdir} FILES ${subdirFiles})
    target_sources(${TARGET_NAME} PRIVATE ${subdirFiles})
endforeach()

if(MSVC)
    set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=${LNLib_DIR}/bin/$<CONFIG>;${VTK_DIR}/bin")
endif()