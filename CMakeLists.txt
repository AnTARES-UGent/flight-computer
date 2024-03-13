cmake_minimum_required(VERSION 3.13)


# Specify the subfolder where your source files are located
set(MAIN_FOLDER "./src/main")
set(IO_FOLDER "./src/io")
set(LIBS_FOLDER "./src/libs")


# initialize pico-sdk from GIT
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project


# Add pico_stdlib library which aggregates commonly used features




# Get list of all files in the subfolder
file(GLOB SRC_SOURCES "${MAIN_FOLDER}/*.cpp")
file(GLOB SRC_HEADERS "${MAIN_FOLDER}/*.h")





# Add the files to your target
#target_link_libraries(antares_flight_computer ${SUBFOLDER_SOURCES} ${SUBFOLDER_HEADERS})

add_executable(antares_flight_computer



    ${SRC_SOURCES}
    ${SRC_HEADERS}


)


include_directories(${IO_FOLDER} ${LIBS_FOLDER})

target_link_libraries(antares_flight_computer pico_stdlib pico_multicore)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(antares_flight_computer)