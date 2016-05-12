-- A solution contains projects, and defines the available configurations
solution "Spelling_Game"
	configurations { "Debug", "Release" }
	location "build"

	-- A project defines one build target
	project "spelling_game"
		location "build"
		kind "ConsoleApp"
		language "C"
		files
		{
			"main.c",
			"spelling_game.h",
			"cvector.h",
			"linenoise.c",
			"linenoise.h",
			"c_utils.c",
			"c_utils.h",
			"basic_types.h"
		}
--      excludes { "vector_template.*" }
--      libdirs { }
--      links { "cunit" } 
		targetdir "build"

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

		configuration { "gmake" }
			buildoptions
			{
			"-std=gnu99", --for posix stuff
			--"-pedantic-errors",
			"-fno-strict-aliasing",
			"-Wunused-variable",
			"-Wreturn-type" 
			}
