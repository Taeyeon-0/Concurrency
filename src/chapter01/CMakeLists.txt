file(GLOB source_files CONFIGURE_DEPENDS "*.cpp")

foreach(src_file ${source_files})
    # Without Extension
    get_filename_component(target_name ${src_file} NAME_WE)
    
    add_executable(${target_name} ${src_file})

    message(STATUS "Created target: ${target_name}")
endforeach()
