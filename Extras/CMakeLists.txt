add_subdirectory(Serialize)
add_subdirectory(ConvexDecomposition)
add_subdirectory(HACD)
add_subdirectory(GIMPACTUtils)

#Maya Dynamica plugin is moved to http://dynamica.googlecode.com

if(USE_GLUT AND GLUT_FOUND)
	add_subdirectory(glui)
endif()
