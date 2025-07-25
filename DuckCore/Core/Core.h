#pragma once

/*
The following external libs can be included by the executable project.

These are the paths that need to be added to the project properties:
$(SolutionDir)Build/Out/DuckCore/$(Platform)_$(Configuration)/
$(SolutionDir)DuckCore/External/lib/$(Configuration)
$(SolutionDir)DuckCore/External/lib/Shared

These libs can be included, on top of DuckCore.lib:
SDL2.lib
SDL2main.lib
SDL2_image.lib
SDL2_ttf.lib
libzmq.lib
OptickCore.lib
sfml-graphics-s.lib
sfml-window-s.lib
sfml-audio-s.lib
sfml-network-s.lib
sfml-system-s.lib
opengl32.lib
openal32.lib
freetype.lib
winmm.lib
gdi32.lib
flac.lib
vorbisenc.lib
vorbisfile.lib
vorbis.lib
ogg.lib
ws2_32.lib
lua.lib
*/

#ifdef _MSC_VER
    #pragma warning(disable : 4100) // Unreferenced formal parameter.
#elif defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic ignored "-Wunused-parameter"
#else
    #error "Unsupported compiler"
#endif

#include <DuckCore/Utilities/Utilities.h>

#include <functional>

namespace DC
{
class Core
{
public:
	static void sStartup(int aArgumentCount, char* aArgumentValues[]);
};

namespace Private
{
	class DeferHelper
	{
	public:
		explicit DeferHelper(std::function<void()> inFunction) : mFunction(Move(inFunction)) {}
		~DeferHelper() { mFunction(); }

	private:
		std::function<void()> mFunction;
	};
}
}

#define defer(x) DC::Private::DeferHelper scoped_defer([&]() { x; })
