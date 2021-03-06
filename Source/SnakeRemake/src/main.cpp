
// Engine includes
#include "SDLSystem.h"
#include "SDLError.h"

// Snake includes
#include "StageMenu.h"
#include "StageGame.h"

#include "Logging.h"
#include <cstdlib>

int main(int argc, char* args[])
{
	try
	{
		const int DRAW_TILE_SIZE = 24;

		// Start up SDL and create window
		tbd::SDLSystem system{DRAW_TILE_SIZE * 16, DRAW_TILE_SIZE * 16 + 20, DRAW_TILE_SIZE}; // TODO: tmp hack to make space for stats below the game

		// TODO: is this indirection necessary?
		system.init();

		// Load media
		system.setStage<tbd::StageGame>();

		// Spin the main program loop
		system.spin();
	}
	catch (const tbd::SDLError& ex)
	{
		LOG_FTL << "Caught tbd::SDLError: " << ex.what();
		return EXIT_FAILURE;
	}
	catch (const std::runtime_error& ex)
	{
		LOG_FTL << "Caught std::runtime_error: " << ex.what();
		return EXIT_FAILURE;
	}
	catch (const std::exception& ex)
	{
		LOG_FTL << "Caught std::exception: " << ex.what();
		return EXIT_FAILURE;
	}
	catch (...)
	{
		LOG_FTL << "Caught unknown exception";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
