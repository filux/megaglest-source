# common libraries

SET(EXTERNAL_LIBS "")
SET(TARGET_NAME "megaglest_g3dviewer")
SET(TARGET_NAME_MANPAGE "${TARGET_NAME}.6")

IF(BUILD_MEGAGLEST_MODEL_VIEWER)
	MESSAGE(STATUS "Will try to build MegaGlest model viewer")

	FIND_PACKAGE(SDL REQUIRED)
	INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
	SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${SDL_LIBRARY})

	FIND_PACKAGE(OpenGL REQUIRED)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
	SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${OPENGL_LIBRARY})

	FIND_PACKAGE(GLEW REQUIRED)
	INCLUDE_DIRECTORIES(${GLEW_INCLUDE_PATH})
	IF(UNIX)
		SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${GLEW_LIBRARY})
	ENDIF()

	IF(NOT WIN32)

		FIND_PACKAGE(XercesC REQUIRED)
		INCLUDE_DIRECTORIES(${XERCESC_INCLUDE})
		SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${XERCESC_LIBRARY})

		# It was noticed that when using MinGW gcc it is essential that 'core' is mentioned before 'base'.
		FIND_PACKAGE(wxWidgets COMPONENTS core base gl REQUIRED)
		# wxWidgets include (this will do all the magic to configure everything)
		include( ${wxWidgets_USE_FILE} )
		SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${wxWidgets_LIBRARIES})
	ELSE()
		SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${PROJECT_SOURCE_DIR}/source/win32_deps/wxWidgets-2.8.10/lib/libwx_mswu-2.8-i586-mingw32msvc.dll.a)
		SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${PROJECT_SOURCE_DIR}/source/win32_deps/wxWidgets-2.8.10/lib/libwx_mswu_gl-2.8-i586-mingw32msvc.dll.a)
		SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${PROJECT_SOURCE_DIR}/source/win32_deps/wxWidgets-2.8.10/lib/libwxpng-2.8-i586-mingw32msvc.a)
		SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${PROJECT_SOURCE_DIR}/source/win32_deps/wxWidgets-2.8.10/lib/libwxjpeg-2.8-i586-mingw32msvc.a)
		SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${PROJECT_SOURCE_DIR}/source/win32_deps/wxWidgets-2.8.10/lib/libwxtiff-2.8-i586-mingw32msvc.a)
		SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${PROJECT_SOURCE_DIR}/source/win32_deps/wxWidgets-2.8.10/lib/libwxzlib-2.8-i586-mingw32msvc.a)

		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/wxWidgets-2.8.10/include/)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/wxWidgets-2.8.10/lib/wx/include/i586-mingw32msvc-msw-unicode-release-static-2.8)

		SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
				       ${PROJECT_SOURCE_DIR}/source/win32_deps/lib
				       ${PROJECT_SOURCE_DIR}/source/win32_deps/xerces-c-src_2_8_0/lib)

		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/include)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/openal-soft-1.12.854/include)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/openal-soft-1.12.854)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/xerces-c-src_2_8_0/include)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/libogg-1.2.1/include)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/lua-5.1/src)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/jpeg-8b)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/lpng141)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/zlib-1.2.5)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/curl-7.21.3/include)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/win32_deps/SDL-1.2.x/include)
				       
		link_directories(${PROJECT_SOURCE_DIR}/source/win32_deps/lib)
		link_directories(${PROJECT_SOURCE_DIR}/source/win32_deps/xerces-c-src_2_8_0/lib)
	ENDIF()

	#########################################################################################
	# megaglest G3D Model Viewer

	SET(DIRS_WITH_SRC
	    .
	     )

	SET(GLEST_MAIN_INCLUDE_ROOT "../glest_game/")
	SET(GLEST_LIB_INCLUDE_ROOT "../shared_lib/include/")

	SET(GLEST_LIB_INCLUDE_DIRS
	    ${GLEST_LIB_INCLUDE_ROOT}platform/common
	#    ${GLEST_LIB_INCLUDE_ROOT}platform/sdl
	    ${GLEST_LIB_INCLUDE_ROOT}platform/posix
	    ${GLEST_LIB_INCLUDE_ROOT}util
	    ${GLEST_LIB_INCLUDE_ROOT}graphics
	    ${GLEST_LIB_INCLUDE_ROOT}graphics/gl
	    ${GLEST_LIB_INCLUDE_ROOT}map
	    ${GLEST_LIB_INCLUDE_ROOT}sound
	    ${GLEST_LIB_INCLUDE_ROOT}xml
            ${GLEST_LIB_INCLUDE_ROOT}xml/rapidxml
	    ${GLEST_MAIN_INCLUDE_ROOT}facilities
	    ${GLEST_MAIN_INCLUDE_ROOT}graphics
	    ${GLEST_MAIN_INCLUDE_ROOT}game
	    ${GLEST_MAIN_INCLUDE_ROOT}global
	    ${GLEST_MAIN_INCLUDE_ROOT}sound)

	IF(WANT_STREFLOP)
		SET(GLEST_LIB_INCLUDE_DIRS
			${GLEST_LIB_INCLUDE_DIRS}
    			${GLEST_LIB_INCLUDE_ROOT}streflop)
	ENDIF()

	INCLUDE_DIRECTORIES( ${GLEST_LIB_INCLUDE_DIRS} )

	IF(WIN32)
		INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/source/shared_lib/include/platform/win32)
		INCLUDE_DIRECTORIES( ${GLEST_LIB_INCLUDE_ROOT}platform/sdl )
	ELSE()
		INCLUDE_DIRECTORIES( ${GLEST_LIB_INCLUDE_ROOT}platform/sdl )
	ENDIF()

	SET(MG_SOURCE_FILES "../glest_game/graphics/particle_type.cpp" "../glest_game/graphics/unit_particle_type.cpp" "../glest_game/global/config.cpp")
	
	FOREACH(DIR IN LISTS DIRS_WITH_SRC)
		INCLUDE_DIRECTORIES( ${DIR} )

		set(SRC_DIR_TO_GLOB ${DIR})
		FILE(GLOB SRC_FILES_FROM_THIS_DIR ${SRC_DIR_TO_GLOB}/*.cpp)
		SET(MG_SOURCE_FILES ${MG_SOURCE_FILES} ${SRC_FILES_FROM_THIS_DIR})
		FILE(GLOB INCLUDE_FILES_FROM_THIS_DIR ${SRC_DIR_TO_GLOB}/*.h)
		SET(MG_INCLUDE_FILES ${MG_INCLUDE_FILES} ${INCLUDE_FILES_FROM_THIS_DIR})	
		IF(APPLE)
			FILE(GLOB SRC_FILES_FROM_THIS_DIR ${SRC_DIR_TO_GLOB}/*.mm)
			#MESSAGE(STATUS "SRC_FILES_FROM_THIS_DIR: ${SRC_FILES_FROM_THIS_DIR}")
			SET(MG_SOURCE_FILES ${MG_SOURCE_FILES} ${SRC_FILES_FROM_THIS_DIR})
			FILE(GLOB SRC_FILES_FROM_THIS_DIR ${SRC_DIR_TO_GLOB}/*.m)
			#MESSAGE(STATUS "SRC_FILES_FROM_THIS_DIR: ${SRC_FILES_FROM_THIS_DIR}")
			SET(MG_SOURCE_FILES ${MG_SOURCE_FILES} ${SRC_FILES_FROM_THIS_DIR})	
			ENDIF(APPLE)
	ENDFOREACH(DIR)
	
        OPTION(WANT_DEV_OUTPATH "use developer friendly output paths" OFF)
        IF(WANT_DEV_OUTPATH)
	        IF(UNIX AND NOT APPLE)
		        SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/mk/linux/)
	        ELSE()
		        SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/data/glest_game/)
	        ENDIF()
        ENDIF()

        SET(HELP2MAN_OUT_PATH ${EXECUTABLE_OUTPUT_PATH})
        IF("${EXECUTABLE_OUTPUT_PATH}" STREQUAL "")
                SET(HELP2MAN_OUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/")
        ENDIF()

        MESSAGE(STATUS "***Note: The final output path for Megaglest G3d Viewer will be [${HELP2MAN_OUT_PATH}]")

	FIND_PROGRAM(HELP2MAN "help2man")

	SET_SOURCE_FILES_PROPERTIES(${MG_INCLUDE_FILES} PROPERTIES HEADER_FILE_ONLY 1)

	ADD_EXECUTABLE(${TARGET_NAME} ${MG_SOURCE_FILES} ${MG_INCLUDE_FILES})

	IF(WANT_STREFLOP)
		TARGET_LINK_LIBRARIES(${TARGET_NAME} streflop)
	ENDIF()

	IF(WIN32)
		TARGET_LINK_LIBRARIES(${TARGET_NAME} libmegaglest)
	ELSE()
		TARGET_LINK_LIBRARIES(${TARGET_NAME} libmegaglest)
	ENDIF()
	TARGET_LINK_LIBRARIES(${TARGET_NAME} ${EXTERNAL_LIBS})

	IF(EXISTS ${HELP2MAN})
		MESSAGE("***-- Found help2man: ${HELP2MAN} about to build manpage in [${HELP2MAN_OUT_PATH}${TARGET_NAME_MANPAGE}]")

                SET(MG_MANPAGE_DESCRIPTION "G3D Model editor for the popular 3D realtime stragegy game")

		IF(EXISTS ${XVFB_EXEC})
			MESSAGE("***-- Found xvfb-run: ${XVFB_EXEC} about to build manpage with it.")

		  	add_custom_target(${TARGET_NAME_MANPAGE} ALL
		    		COMMAND ${XVFB_EXEC} --auto-servernum --server-num=770 ${HELP2MAN} --name='${MG_MANPAGE_DESCRIPTION}' --section=6 -N -o ${HELP2MAN_OUT_PATH}${TARGET_NAME_MANPAGE} ${HELP2MAN_OUT_PATH}${TARGET_NAME}
		    	DEPENDS ${TARGET_NAME})
		ELSE()
		  	add_custom_target(${TARGET_NAME_MANPAGE} ALL
		    		COMMAND ${HELP2MAN} --name='${MG_MANPAGE_DESCRIPTION}' --section=6 -N -o ${HELP2MAN_OUT_PATH}${TARGET_NAME_MANPAGE} ${HELP2MAN_OUT_PATH}${TARGET_NAME}
		    	DEPENDS ${TARGET_NAME})
		ENDIF()
	ENDIF()

        # Requires an install prefix for the items below to work
        IF(NOT CMAKE_INSTALL_PREFIX STREQUAL "")
	        # Installation of the program
	        INSTALL(TARGETS 
		        ${TARGET_NAME} 
		        DESTINATION ${MEGAGLEST_BIN_INSTALL_PATH})

	        IF(EXISTS ${HELP2MAN})
         		MESSAGE(STATUS "**NOTE: Will Install manpage [${TARGET_NAME_MANPAGE}] to [${MEGAGLEST_MANPAGE_INSTALL_PATH}]")	

		        # Installation of the program manpage file
		        INSTALL(FILES 
		          "${HELP2MAN_OUT_PATH}${TARGET_NAME_MANPAGE}"
		          DESTINATION ${MEGAGLEST_MANPAGE_INSTALL_PATH})
	        ENDIF()

                # Installation of the program config and image files
	        INSTALL(FILES 
	          "${PROJECT_SOURCE_DIR}/mk/shared/g3dviewer.ico"
	          DESTINATION ${MEGAGLEST_DATA_INSTALL_PATH})

	        # Installation of the program desktop file
                SET(MG_DESKTOP_FILE ${PROJECT_SOURCE_DIR}/mk/linux/megaglest_g3dviewer.desktop)

                INSTALL(FILES
	          "${MG_DESKTOP_FILE}"
	          DESTINATION ${MEGAGLEST_DESKTOP_INSTALL_PATH})

        ENDIF()
ENDIF()
