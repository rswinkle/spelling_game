-- A solution contains projects, and defines the available configurations
solution "Spelling_Game"
   configurations { "Debug", "Release" }
   location "build"
 
   -- A project defines one build target
   project "spelling_game"
      location "build"
      kind "ConsoleApp"
      language "C"
      files { "*.h", "*.c" }
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
 
      configuration { "linux", "gmake" }
         buildoptions {
         "-std=c99", "-pedantic-errors", "-fno-strict-aliasing",
         "-Wunused-variable", "-Wreturn-type" 
         }
