add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/CL")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/CL_HPP")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Core")

set(LinkCL_SOURCE_FILES
    "${LinkCL_CL_SOURCE_FILES}"
    "${LinkCL_CL_HPP_SOURCE_FILES}"
    "${LinkCL_CORE_SOURCE_FILES}"
    CACHE INTERNAL "" FORCE)

set(LinkCL_HEADER_FILES
    "${LinkCL_CL_HEADER_FILES}"
    "${LinkCL_CL_HPP_HEADER_FILES}"
    "${LinkCL_CORE_HEADER_FILES}"
    CACHE INTERNAL "" FORCE)
