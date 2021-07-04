if(NOT COMMAND nx_generate_nacp)
    message(FATAL_ERROR "The `nx_generate_nacp` cmake command is not available. Please use an appropriate Nintendo Switch toolchain.")
endif()

if(NOT COMMAND nx_create_nro)
    message(FATAL_ERROR "The `nx_create_nro` cmake command is not available. Please use an appropriate Nintendo Switch toolchain.")
endif()
