cmake_minimum_required(VERSION 3.25)
project(Game)
set(CompileFlags -Wall -Wextra -Werror)
file(GLOB_RECURSE SourceFiles src/*.cpp)
file(GLOB_RECURSE IncludeFiles include/*.hpp)

add_executable(Game ${IncludeFiles} ${SourceFiles})
set_target_properties(Game PROPERTIES
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	EXPORT_COMPILE_COMMANDS ON
)
target_include_directories(Game PRIVATE include)
target_compile_options(Game PRIVATE ${CompileFlags})
