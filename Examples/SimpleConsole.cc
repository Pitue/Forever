#include <common.h>

#include <Console.h>

int main(int argc, char** argv) {
	try {
		Forever::ERROR_HANDLE.set_mode(Forever::ErrorHandleMode::SHOW_MESSAGE_BOX);

		Forever::Initialize(SDL_INIT_EVERYTHING, -1, -1, true);
		Forever::Font font = TTF_OpenFont("arial.ttf", 20);

		if (font) {
			Forever::Console con(32, 120, font);

			con.Write("Your name? ");
			std::string name = con.ReadLine();
			con << "Hello, " << name << "!\n";

			con.set_writable(true);
			while (con) {
				if (con.LineInBuffer()) {
					std::string command = con.ReadFromBuffer();

					if (std::strcmp(command.c_str(), "quit") == 0) {
						con.Quit();
					}
					else {
						con.Write("Input: ");
						con.WriteLine(command.c_str());
					}
				}
				con.Update();
			}
			TTF_CloseFont(font);
		}
		else {
			Forever::ERROR_HANDLE.Handle(TTF_GetError());
		}
	}
	catch (std::exception& ex) {
		Forever::ERROR_HANDLE.Handle(ex.what());
	}

	Forever::Quit();
	return 0;
}