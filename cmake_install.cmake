# Install script for directory: /home/brad/heekscad/heekscnc

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/heekscnc" TYPE FILE FILES
    "/home/brad/heekscad/heekscnc/area_funcs.py"
    "/home/brad/heekscad/heekscnc/actp_funcs.py"
    "/home/brad/heekscad/heekscnc/kurve_funcs.py"
    "/home/brad/heekscad/heekscnc/backplot.py"
    "/home/brad/heekscad/heekscnc/turning.py"
    "/home/brad/heekscad/heekscnc/circular_pocket.py"
    "/home/brad/heekscad/heekscnc/ocl_funcs.py"
    "/home/brad/heekscad/heekscnc/roughing_funcs.py"
    "/home/brad/heekscad/heekscnc/pycnc/wxCAMWindow.py"
    "/home/brad/heekscad/heekscnc/pycnc/NCCode.py"
    "/home/brad/heekscad/heekscnc/pycnc/wxProgramDlg.py"
    "/home/brad/heekscad/heekscnc/pycnc/PopupMenu.py"
    "/home/brad/heekscad/heekscnc/pycnc/Profile.py"
    "/home/brad/heekscad/heekscnc/pycnc/wxPocketDlg.py"
    "/home/brad/heekscad/heekscnc/pycnc/PyProcess.py"
    "/home/brad/heekscad/heekscnc/pycnc/RawMaterial.py"
    "/home/brad/heekscad/heekscnc/pycnc/wxPictureWindow.py"
    "/home/brad/heekscad/heekscnc/pycnc/Operations.py"
    "/home/brad/heekscad/heekscnc/pycnc/Tools.py"
    "/home/brad/heekscad/heekscnc/pycnc/consts.py"
    "/home/brad/heekscad/heekscnc/pycnc/SpeedOp.py"
    "/home/brad/heekscad/heekscnc/pycnc/Tree.py"
    "/home/brad/heekscad/heekscnc/pycnc/HeeksCNC.py"
    "/home/brad/heekscad/heekscnc/pycnc/Tool.py"
    "/home/brad/heekscad/heekscnc/pycnc/wxNiceTextCtrl.py"
    "/home/brad/heekscad/heekscnc/pycnc/NoCad.py"
    "/home/brad/heekscad/heekscnc/pycnc/CNCConfig.py"
    "/home/brad/heekscad/heekscnc/pycnc/Machine.py"
    "/home/brad/heekscad/heekscnc/pycnc/wxHDialog.py"
    "/home/brad/heekscad/heekscnc/pycnc/wxProfile.py"
    "/home/brad/heekscad/heekscnc/pycnc/Pocket.py"
    "/home/brad/heekscad/heekscnc/pycnc/Object.py"
    "/home/brad/heekscad/heekscnc/pycnc/MachineState.py"
    "/home/brad/heekscad/heekscnc/pycnc/DepthOp.py"
    "/home/brad/heekscad/heekscnc/pycnc/Operation.py"
    "/home/brad/heekscad/heekscnc/pycnc/wxProgramWindow.py"
    "/home/brad/heekscad/heekscnc/pycnc/Program.py"
    "/home/brad/heekscad/heekscnc/pycnc/Cad.py"
    "/home/brad/heekscad/heekscnc/pycnc/wxOutputWindow.py"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/brad/heekscad/heekscnc/src/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/brad/heekscad/heekscnc/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/brad/heekscad/heekscnc/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
