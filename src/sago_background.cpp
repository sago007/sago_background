#include <iostream>
#include <boost/program_options.hpp>
#include <physfs.h>
#include "SDL.h"
#include <SDL_image.h>
#include "sago/SagoSpriteHolder.hpp"
#include "sago/SagoTextBox.hpp"
#include "sago/SagoMiscSdl2.hpp"

#ifndef VERSIONNUMBER
#define VERSIONNUMBER "0.1.0"
#endif

int main(int argc, const char* argv[]) {
	PHYSFS_init(argv[0]);
	boost::program_options::options_description desc("Options");
	desc.add_options()
	("version", "Print version information and quit")
	("help,h", "Print basic usage information to stdout and quit")
	;
	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
	boost::program_options::notify(vm);
	if (vm.count("help")) {
		std::cout << desc << "\n";
		return 0;
	}
	if (vm.count("version")) {
		std::cout << "sago_background " << VERSIONNUMBER << "\n";
		return 0;
	}
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		sago::SagoFatalErrorF("Unable to init SDL: %s", SDL_GetError());
	}
	TTF_Init();
	atexit(SDL_Quit);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	//Open video
	int createWindowParams = 0;
	createWindowParams |= SDL_WINDOW_RESIZABLE;
	SDL_Window* sdlWindow = SDL_CreateWindow("Sago background " VERSIONNUMBER,
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									800, 800,
									createWindowParams );
	
	int rendererFlags = 0;
	SDL_Renderer* renderer = SDL_CreateRenderer(sdlWindow, -1, rendererFlags);

	while (1) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(sdlWindow);


	return 0;
}
