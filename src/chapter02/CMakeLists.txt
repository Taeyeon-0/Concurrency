file(GLOB source_files CONFIGURE_DEPENDS "*.cpp")

foreach(src_file ${source_files})
    get_filename_component(file_name ${src_file} NAME)
    string(REPLACE "." "_" target_name ${file_name})
    add_executable(${target_name} ${src_file})
    message(STATUS "Created target: ${target_name}")
endforeach()
