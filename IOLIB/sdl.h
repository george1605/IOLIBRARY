// SDL wrapper
#pragma once
#include <SDL.h>
#include "lib.h"
#include "buffer.h"
#define _CUSTOM
#undef main

#ifdef _WIN32
#include <memoryapi.h>
#include <Windows.h>
#endif

namespace io
{
	typedef SDL_Event sdlevt;
	typedef SDL_Rect sdlrect;
	typedef SDL_Thread sdlthrd;
	typedef SDL_Renderer* sdlrender;
	bool __sdl_init = false;

	bool has_sdl()
	{
		return loadlib((char*)LIB(SDL_LIB)) != nullptr;
	}

	bool has_jpeg()
	{
		return loadlib((char*)LIB(JPEG_LIB)) != nullptr;
	}

	void load_image(const char* name, int cx, int cy)
	{
		if (!has_jpeg())
		{
#ifdef _WIN32
			LoadImageA(GetModuleHandle(NULL), (LPCSTR)name, IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
#endif
		}

	}

	void* __sdl_alloc(size_t size)
	{
#ifdef _WIN32
		HANDLE heap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 1024, BUFLIMIT);
		void* res = (void*)HeapAlloc(heap, 0, size);
		return res;
#endif

#ifdef __linux__
#include <unistd.h>
		void* x = sbrk(0);
		brk(x + size + 1);
		return x;
#endif

#ifdef __KOS__ // my os way 
		return alloc(0, size);
#endif
	}

	void __sdl_free(void* ptr)
	{
#ifdef _CUSTOM
		char* x = (char*)ptr;
		if (x == nullptr)
			return;
		while (*x != 0) // equivalent to memset() 
			*x = 0, x++;


#endif

#ifdef __KOS__
		free(ptr);
#endif
	}

	SDL_malloc_func sdl_malloc = __sdl_alloc;
	SDL_free_func sdl_free = __sdl_free;

	void from_rgb(int rgb, uint8_t arr[3])
	{
		arr[0] = (rgb & 0xff);
		arr[1] = (rgb & 0xffff) >> 8;
		arr[2] = (rgb & 0xffffff) >> 16;
	}
	
	size_t to_rgb(uint8_t r, uint8_t g, uint8_t b)
	{
		size_t x = r | (g << 8) | (b << 16);
		return x;
	}

	void delay_sec(int s = 1)
	{
		SDL_Delay(s * 1000);
	}

	class sdlwin
	{
	private:
		SDL_Window* winptr;
		SDL_Surface* context;
		SDL_Renderer* renderer = nullptr;
	public:
		bool closed = false;
		sdlwin()
		{
			if (!__sdl_init)
				SDL_Init(SDL_INIT_EVERYTHING), __sdl_init = true;
			
			this->winptr = SDL_CreateWindow("GAME",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				1000, 1000, 0);
			renderer = SDL_CreateRenderer(winptr, -1, SDL_RENDERER_ACCELERATED);
		}
		sdlwin(int w, int h)
		{
			if (!__sdl_init)
				SDL_Init(SDL_INIT_EVERYTHING), __sdl_init = true;

			this->winptr = SDL_CreateWindow("nullptr",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				w, h, 0);
			renderer = SDL_CreateRenderer(winptr, -1, SDL_RENDERER_ACCELERATED);
		}
		sdlwin(const char* name)
		{

		}
		~sdlwin()
		{
			closed = true;
			SDL_DestroyWindow(winptr);
		}
		void add_rect()
		{
			SDL_Rect x;
			context = SDL_GetWindowSurface(this->winptr);
		}
		io::pair<int, int> size()
		{
			io::pair<int, int> k;
			SDL_GetWindowSize(winptr, &k.first, &k.second);
			return k;
		}
		void clear(uint8_t arr[3])
		{
			SDL_SetRenderDrawColor(renderer, arr[0], arr[1], arr[2], 255);
			SDL_RenderClear(renderer);
		}
	};
#define SDL_EVENT(evt) SDL_PollEvent(&evt)
}