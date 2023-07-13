include_directories(${SRC_INCLUDE_DIR})

set(UTILS_SRC)
aux_source_directory(src/utils UTILS_SRC)
add_library(utils ${UTILS_SRC})
set_target_properties(utils PROPERTIES EXPORT_NAME utils)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/utils
        DESTINATION include/utils
        FILES_MATCHING PATTERN "*.h")
install(TARGETS utils
        EXPORT utils_targets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_SOURCE_DIR}/assets/thirdparty/libu.a DESTINATION lib)
