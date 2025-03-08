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

#pragma warning( disable : 4100 ) // Unreferenced formal parameter.

namespace DC
{
class Core
{
public:
	static void sStartup();
};
}