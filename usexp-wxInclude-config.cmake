# WXINCLUDE_FOUND - wxInclude was found
# WXINCLUDE_EXE - the wxInclude executable
set(prj wxInclude)
# this file (-config) installed to share/cmake (see top-level CMakeLists.txt)
get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(XP_ROOTDIR "${SELF_DIR}/../.." ABSOLUTE)
# targets file (-targets) installed to bin${NUMBITS}/cmake
include(${XP_ROOTDIR}/bin${NUMBITS}/cmake/${prj}-targets.cmake)
string(TOUPPER ${prj} PRJ)
set(${PRJ}_EXE ${prj})
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(${prj}
  REQUIRED_VARS
    ${PRJ}_EXE
  )
mark_as_advanced(${PRJ}_EXE)
