cmake_minimum_required(VERSION 3.13)
project(ArchiMage)
# Parametre
set(CMAKE_BUILD_TYPE Debug) # À commenter lors du rendu
set(CMAKE_CXX_STANDARD 17)

# Project
set(SRCS
	"sources/main.cpp"
	"sources/Drawable.cpp"
	"sources/DrawableObject.cpp"
)

set(HEADERS
	"headers/Drawable.hpp"
	"headers/DrawableObject.hpp"
)

set(SHADERS
	"shaders/point_color.frag"
	"shaders/main_shader.vert"
	"objects/bunny.off"
	"objects/sphere.off"
)


add_executable(main ${HEADERS} ${SRCS})

# Pour chaque shader :
foreach(SHADER IN LISTS SHADERS)
	# On a un chemin dans le build :
	SET(CURRENT_SHADER "${CMAKE_CURRENT_BINARY_DIR}/${SHADER}")
	# ET on a un chemin dans les sources :
	SET(SOURCE_SHADER "${CMAKE_SOURCE_DIR}/${SHADER}")

	# Si il y a déjà un fichier copié :
	IF(EXISTS ${CURRENT_SHADER})
		# On test si la source existe toujours :
		IF(EXISTS ${SOURCE_SHADER})
			# On calcul leurs SHA256 :
			FILE(SHA256 ${CURRENT_SHADER} A)
			FILE(SHA256 ${SOURCE_SHADER} B)
			# Si les hash sont différents :
			IF(NOT ${A} MATCHES ${B})
				# On copie le fichier
				message(STATUS "Copying: ${SHADER}")
				configure_file(${SOURCE_SHADER} ${CURRENT_SHADER} COPYONLY)
				message(STATUS "Copying: ${SHADER} - done")
			endif()
		endif()
	else() # Sinon, si le fichier ne se trouve pas dans le build :
		# On regarde si la source existe
		IF(EXISTS ${SOURCE_SHADER})
			# Et on l'a copie
			message(STATUS "Copying: ${SHADER}")
			configure_file(${SOURCE_SHADER} ${CURRENT_SHADER} COPYONLY)
			message(STATUS "Copying: ${SHADER} - done")
		else() # Sinon, on affiche une erreur :
			message(STATUS "ERROR : SOURCE \"${SOURCE_SHADER}\" NOT FNOUD !")
		endif()
	endif()
endforeach()

target_compile_options(main PUBLIC "-Wall")

#My libs
target_include_directories(main PUBLIC "include" BEFORE)
add_subdirectory("include/lib_objectsReader")
add_subdirectory("include/lib_shaders")

#openGL
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLU_INCLUDE_DIRS})

target_link_libraries(
	main
	${OPENGL_LIBRARIES}
	${GLUT_LIBRARY}
	${GLEW_LIBRARIES}
	${GLU_LIBRARIES}
	shaders
	objectsReader
)
