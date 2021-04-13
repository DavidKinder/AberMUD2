project(abermud)
cmake_minimum_required(VERSION 3.16)

# Having better control over the compilation flags was kind of the
# primary purpose of having a CMakeLists.txt in the first place.
set(CMAKE_C_FLAGS "-Wno-implicit-int ${CMAKE_C_FLAGS}")

link_libraries(crypt)
set(WORLDFILE "${CMAKE_CURRENT_BINARY_DIR}/worldfile")
add_definitions(-DWORLD="${WORLDFILE}")

add_executable(hmk make.h.c)

add_custom_target(
  files_header
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/files.h
  )

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/files.h
  COMMAND hmk >files.h
  DEPENDS hmk 
  IMPLICIT_DEPENDS
  )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(mud.exe
  tk.c parse.c objsys.c extra.c magic.c blood.c weather.c obdat.c new1.c
  support.c zones.c mobile.c bprintf.c bbc.c blib.c opensys.c gamego.c ndebug.c
  key.c packer.c newuaf.c frob.c)
add_dependencies(mud.exe files_header)
add_executable(mud.1
  blib.c gmain2.c gmainstubs.c gmlnk.c obdat.c)
add_dependencies(mud.1 files_header)
add_executable(makeworld.util makeworld.c blib.c)
add_executable(ogenerate ogen.c blib.c)
add_executable(makeuaf makeuaf.c)

# Reset the mud
add_custom_target(
  reset
  # Originally from install.sh
  COMMAND ${CMAKE_COMMAND} -E remove TEXT SNOOP EXAMINES
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/TEXT TEXT
  COMMAND ${CMAKE_COMMAND} -E make_directory SNOOP
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/EXAMINES EXAMINES
  COMMAND ${CMAKE_COMMAND} -E remove mud_syslog reset_t reset_n user_file
  COMMAND ${CMAKE_COMMAND} -E touch mud_syslog reset_t reset_n user_file
  COMMAND ${CMAKE_COMMAND} -E remove ${WORLDFILE}
  # Originally from install2.sh
  COMMAND makeworld.util
  COMMAND ${CMAKE_COMMAND} -E echo "Game universe intialised"
  # ob.in read by ogenerate to make ob.out
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/ob.in ob.in
  COMMAND ogenerate >ob.log
  COMMAND ${CMAKE_COMMAND} -E copy ob.out reset_data
  COMMAND ${CMAKE_COMMAND} -E echo "Reset data generated"
  COMMAND makeuaf >uaf.rand
  DEPENDS makeworld.util ogenerate makeuaf
  )

set_property(
  TARGET reset
  APPEND
  PROPERTY ADDITIONAL_CLEAN_FILES
  ${CMAKE_CURRENT_BINARY_DIR}/files.h
  ${WORLDFILE}
  TEXT SNOOP EXAMINES
  mud_syslog reset_t reset_n user_file reset_data ob.in ob.log ob.out uaf.rand
  )
