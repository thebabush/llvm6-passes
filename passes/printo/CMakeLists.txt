add_llvm_loadable_module(PrintoPass
    # List your source files here.
    Printo.cpp

    PLUGIN_TOOL
    opt
)

# Use C++11 to compile your pass (i.e., supply -std=c++11).
target_compile_features(PrintoPass PRIVATE cxx_range_for cxx_auto_type)

# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
set_target_properties(PrintoPass PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)

find_package(OpenSSL)
add_definitions(${OPENSSL_DEFINITIONS})
target_include_directories(PrintoPass PRIVATE ${OPENSSL_INCLUDE_DIRS})
target_link_libraries(PrintoPass ${OPENSSL_LIBRARIES})

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(PrintoPass PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)
