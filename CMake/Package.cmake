set(CPACK_INSTALL_PREFIX /R-Type)

IF (NOT WIN32)
    set(CPACK_SET_DESTDIR true)
ENDIF()
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt)
set(CPACK_PACKAGE_EXECUTABLES "RType")
set(CPACK_PACKAGING_INSTALL_PREFIX "/R-Type")

set(CPACK_DEBIAN_PACKAGE_NAME "RType")
set(CPACK_DEBIAN_PACKAGE_CONTACT "idk@gmail.com")
set(CPACK_DEBIAN_PACKAGE_VERSION "1.0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "RType")

set(CPACK_DMG_BACKGROUND_IMAGE ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Installer/installer_dragndrop.png)
set(CPACK_DMG_DS_STORE ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Installer/DragNDrop_DS_Store)

cpack_add_component(applications
        REQUIRED
        DISPLAY_NAME "RType"
        DESCRIPTION "RType game"
        GROUP Runtime
        INSTALL_TYPES Full)

if(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "TGZ;DEB;RPM")
endif()
if (APPLE)
    set(CPACK_GENERATOR "TGZ;DragNDrop")
endif()
include(CPack)