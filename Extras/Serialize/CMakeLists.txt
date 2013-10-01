
if(BUILD_BLEND_DEMO OR INTERNAL_UPDATE_SERIALIZATION_STRUCTURES)
	add_subdirectory(BlenderSerialize)
endif()


if(INTERNAL_UPDATE_SERIALIZATION_STRUCTURES)

	# makesdna and HeaderGenerator are for advanced use only
	# makesdna can re-generate the binary DNA representing the Bullet serialization structures
	# Be very careful modifying any of this, otherwise the .bullet format becomes incompatible

	add_subdirectory(BulletFileLoader)
	add_subdirectory(BulletXmlWorldImporter)
	add_subdirectory(BulletWorldImporter)
	add_subdirectory(HeaderGenerator)
	add_subdirectory(makesdna)

else()

	add_subdirectory(BulletFileLoader)
	add_subdirectory(BulletXmlWorldImporter)
	add_subdirectory(BulletWorldImporter)

endif()

