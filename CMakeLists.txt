## Includes
include_directories(
	/usr/include/x86_64-linux-gnu/qt5
		/usr/include/Qca-qt5/QtCrypto
)

## Helpers
if(NOT WIN32)
	string(ASCII 27 Esc)
	set(ColorReset  "${Esc}[m")
	set(ColorBold   "${Esc}[1m")
	set(Red         "${Esc}[31m")
	set(Green       "${Esc}[32m")
	set(Yellow      "${Esc}[33m")
	set(Blue        "${Esc}[34m")
	set(Magenta     "${Esc}[35m")
	set(Cyan        "${Esc}[36m")
	set(White       "${Esc}[37m")
	set(BoldRed     "${Esc}[1;31m")
	set(BoldGreen   "${Esc}[1;32m")
	set(BoldYellow  "${Esc}[1;33m")
	set(BoldBlue    "${Esc}[1;34m")
	set(BoldMagenta "${Esc}[1;35m")
	set(BoldCyan    "${Esc}[1;36m")
	set(BoldWhite   "${Esc}[1;37m")
endif()

## CMake Policy
cmake_policy(SET CMP0005 NEW)

## HeimdallGI File Paths
set(HGI_Config_File        "/var/websites/tuxns/source/api/application.ini")
set(HGI_Static_Files       "/var/websites/tuxns/htdocs")
set(HGI_Views              "/var/websites/tuxns/source/views")

## Normalize File Paths
execute_process(COMMAND realpath -z ${HGI_Config_File}  OUTPUT_VARIABLE HGI_Config_File)
execute_process(COMMAND realpath -z ${HGI_Static_Files} OUTPUT_VARIABLE HGI_Static_Files)
execute_process(COMMAND realpath -z ${HGI_Views}        OUTPUT_VARIABLE HGI_Views)

## Definitions
add_definitions(
	-DHGI_CONFIG_FILE="${HGI_Config_File}"
	-DHGI_STATIC_FILES="${HGI_Static_Files}"
	-DHGI_VIEWS="${HGI_Views}"
)

## Output
message("${Red}HeimdallGI Config File: ${ColorReset}  ${Cyan}${HGI_Config_File}${ColorReset}")
message("${Red}HeimdallGI Static Files:${ColorReset}  ${Cyan}${HGI_Static_Files}${ColorReset}")
message("${Red}HeimdallGI View Files:  ${ColorReset}  ${Cyan}${HGI_Views}${ColorReset}")

## CMake Minimum Version
cmake_minimum_required(VERSION 3.2)

## Project Name
project(HeimdallGI)

## CMake Settings & Configuration
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")

## Include our QCA sources
include(QtCrypto/CMakeLists.txt)

## Source Headers & Files
set(SOURCE_FILES
	./Abstract/Endpoint.h
	./Abstract/PgModel.h
	./Cryptography/AES.h
	./CGI.h
	./Configuration.h
	./DBI.h
	./ErrorController.h
	./HTML.h
	./Log.h
#	./MaxMind.h
	./Pool/Database.h
	./Router.h
	./Template.h
	./View.h
	./Abstract/Endpoint.cpp
	./Abstract/PgModel.cpp
	./Cryptography/AES.cpp
	./CGI.cpp
	./Configuration.cpp
	./DBI.cpp
	./ErrorController.cpp
	./HTML.cpp
	./Log.cpp
#	./MaxMind.cpp
	./Pool/Database.cpp
	./Router.cpp
	./Template.cpp
	./View.cpp
	./main.cpp
)

## Automoc
set(CMAKE_AUTOMOC ON)

## Qt5 Packages
find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5Sql)
find_package(Qt5Xml)

## Executable
add_executable(app.hgi ${SOURCE_FILES})

## Links

target_link_libraries(app.hgi Qt5::Core Qt5::Network Qt5::Sql)

