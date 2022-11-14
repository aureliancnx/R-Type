# Install required system libraries by default
include(InstallRequiredSystemLibraries)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(X_VCPKG_APPLOCAL_DEPS_INSTALL ON)

# Put assets in installation process
# and RType executable in the root folder of destination
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

install(DIRECTORY "${PROJECT_SOURCE_DIR}/Assets/" DESTINATION "Assets")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/Maps/" DESTINATION "Maps")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/Binaries/" DESTINATION ".")

# Set installation prefix
set(CPACK_INSTALL_PREFIX /R-Type)

# WiX doesn't allow us to use CPACK_SET_DESTDIR, so we're using this
# if() trick to make it work on other operating systems.
IF (NOT WIN32)
    set(CPACK_SET_DESTDIR true)
ENDIF()

# Add license, so it's displayed in the installers
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt)

# Add RType as the main executable
set(CPACK_PACKAGE_EXECUTABLES "RType" "RType")
set(CPACK_PACKAGING_INSTALL_PREFIX "/R-Type")

# CPack configuration for DEB/RPM package generation
set(CPACK_DEBIAN_PACKAGE_NAME "RType")
set(CPACK_DEBIAN_PACKAGE_CONTACT "idk@gmail.com")
set(CPACK_DEBIAN_PACKAGE_VERSION "1.0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "RType")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-dev")

# CPack configuration for DMG package generation
set(CPACK_DMG_BACKGROUND_IMAGE ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Installer/installer_dragndrop.png)
set(CPACK_DMG_DS_STORE ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Installer/DragNDrop_DS_Store)

if (${CMAKE_INSTALL_PREFIX} MATCHES "/_CPack_Packages/.*/(TGZ|ZIP)/")
    # Flatten the directory structure such that everything except the header files is placed in root.
    file(GLOB bin_files LIST_DIRECTORIES FALSE ${CMAKE_INSTALL_PREFIX}/bin/*)
    file(GLOB lib_files LIST_DIRECTORIES FALSE ${CMAKE_INSTALL_PREFIX}/lib/*)
    foreach(file ${bin_files} ${lib_files})
        get_filename_component(file_name ${file} NAME)
        execute_process(
                COMMAND ${CMAKE_COMMAND} -E rename
                ${file}
                ${CMAKE_INSTALL_PREFIX}/${file_name}
        )
    endforeach()
    execute_process( COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_INSTALL_PREFIX}/bin)
    execute_process( COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_INSTALL_PREFIX}/lib)
endif()

set(CPACK_SOURCE_INSTALLED_DIRECTORIES
        "${CMAKE_BINARY_DIR}/;/")

# Add RType component
cpack_add_component(applications
        REQUIRED
        DISPLAY_NAME "RType"
        DESCRIPTION "RType game"
        GROUP Runtime
        INSTALL_TYPES Full)

if(UNIX AND NOT APPLE)
    # Generate DEB, RPM and a tarball with Linux
    set(CPACK_GENERATOR "TGZ;DEB;RPM")
endif()

if (APPLE)
    # Generated DMG (DragNDrop) and tarball with MacOS
    set(CPACK_GENERATOR "TGZ;DragNDrop")
endif()

if (WIN32)
    # Generated WiX and tarball with Windows
	set(CPACK_WIX_PRODUCT_ICON ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Installer/RTypeIcon.ico)
    set(CPACK_WIX_UPGRADE_GUID "887A8BAC-1A47-41CC-B869-EBF64138F6C0")
    set(CPACK_GENERATOR "TGZ;WIX")
endif()

# Include CPack
include(CPack)