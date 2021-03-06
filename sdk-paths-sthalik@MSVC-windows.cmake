#
# qtbase configure line for safekeeping
#

# "../configure" -prefix d:\dev\qt-5.10.0 -no-ico -no-gif -no-libjpeg   \
# -opengl desktop -no-angle -no-fontconfig -no-harfbuzz                 \
# -nomake tests -no-mp -release -opensource -shared -confirm-license    \
# -no-freetype -force-debug-info -separate-debug-info                   \
# -make-tool jom -platform win32-msvc

# remember to change -MD to -MT in mkspecs/
# also add CFLAGS -Zi and LFLAGS -DEBUG

set(__depdir "${CMAKE_CURRENT_LIST_DIR}/../opentrack-depends")

function(setq name value)
    set("${name}" "${__depdir}/${value}" CACHE INTERNAL "" FORCE)
endfunction()

set(opentrack_install-debug-info TRUE CACHE INTERNAL "" FORCE)
set(opentrack_maintainer-mode TRUE CACHE INTERNAL "" FORCE)

setq(Qt5_DIR "../qt-5.12.0/lib/cmake/Qt5")
setq(OpenCV_DIR "opencv/build")

setq(SDK_ARUCO_LIBPATH "aruco/build/src/aruco.lib")
setq(EIGEN3_INCLUDE_DIR "eigen")

setq(SDK_FSUIPC "fsuipc")
setq(SDK_HYDRA "SixenseSDK")

setq(SDK_RIFT_140 "LibOVR-140/build")

setq(SDK_VALVE_STEAMVR "steamvr")
setq(SDK_VJOYSTICK "vjoystick")

setq(SDK_REALSENSE "RSSDK-R2")

if(CMAKE_GENERATOR STREQUAL "NMake Makefiles")
    set(CMAKE_MAKE_PROGRAM "jom" CACHE STRING "" FORCE)
endif()
