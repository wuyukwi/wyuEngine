set(third_party_folder ThirdParty)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(json11)


if(IMGUI)
	 include(imgui.cmake)
	 set_target_properties(imgui PROPERTIES FOLDER ${third_party_folder}/imgui)
endif()

set_target_properties(json11 PROPERTIES FOLDER "3rdparty")
set_target_properties(imgui PROPERTIES FOLDER "3rdparty")

