#ifndef __FOREVER_ERROR_HANDLE_H__
#define __FOREVER_ERROR_HANDLE_H__

#include <mutex>
#include <iostream>
#include <fstream>

#include "define.h"
#include "enum.h"

namespace fr {
	class FOREVER_API ErrorHandle {
		std::mutex* mutex_;
		std::fstream* file_handle_;
		ErrorHandleMode mode_;

		bool warnings_;
	public:
		inline ErrorHandle(ErrorHandleMode mode = ErrorHandleMode::SHOW_MESSAGE_BOX, const char* log_file = "log.dat", bool warnings = true)
			: mutex_{ new std::mutex }, file_handle_{ new std::fstream }, mode_{ mode }, warnings_{ warnings } {
			std::scoped_lock(mutex_);

			file_handle_->open(log_file, std::ios::out | std::ios::app);
			if (!file_handle_->is_open()) file_handle_->open(log_file, std::ios::out | std::ios::trunc);
		}
		inline ~ErrorHandle() {
			if (file_handle_) {
				if (file_handle_->is_open()) file_handle_->close();
				delete file_handle_;
			}
			if (mutex_) delete mutex_;
		}

		inline void ShowWarnings(bool show = true) {
			warnings_ = show;
		}
		inline void Warning(const std::string& msg, SDL_Window* parent) {
#ifdef _DEBUG
			if (warnings_) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Forever: Warning", msg.c_str(), parent);
#endif
		}

		inline const ErrorHandle& Handle (const char* msg) const {
			Handle(std::string(msg));
			return *this;
		}
		inline const ErrorHandle& Handle(const std::string& msg) const {
			std::scoped_lock(mutex_);

			if (mode_ == ErrorHandleMode::LOG_IN_FILE) {
				file_handle_->write(msg.c_str(), msg.length());
				if (!file_handle_->good())  throw std::runtime_error(msg);
			}
			else if (mode_ == ErrorHandleMode::PRINT_TO_CONSOLE) {
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, msg.c_str());

				/*
				std::cerr.write(msg.c_str(), msg.length());
				if (!std::cerr.good()) throw std::runtime_error(msg);
				*/
			}		
			else if (mode_ == ErrorHandleMode::SHOW_MESSAGE_BOX) {
				if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Forever: Error", msg.c_str(), NULL) != 0) {
					throw std::runtime_error(msg);
				}
			}
			else if (mode_ == ErrorHandleMode::THROW_ERROR) {
				throw std::runtime_error(msg);
			}
			return *this;
		}
		inline void set_mode(ErrorHandleMode mode) {
			std::scoped_lock(mutex_);
			mode_ = mode;
		}
	};
}

#endif // !__FOREVER_ERROR_HANDLE_H__
