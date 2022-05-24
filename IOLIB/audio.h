#pragma once
#include "buffer.h"
#include "smath.h"
#ifdef _WIN32
#include <mmeapi.h>
#endif
#define WSTR(x) L ## x

namespace io
{
	class audio_file
	{
	private:
		char* fname;
	public:
		audio_file(const char* fname)
		{
			this->fname = (char*)fname;
		}
		void play()
		{
#ifdef _WIN32
#include <Windows.h>
#include <mmsystem.h>
#include <xaudio2.h>
#pragma comment(lib, "winmm.lib")

			

#else
			system(fname);
#endif
		}

	};

	class audio_buffer : public buffer
	{
	public:
		audio_buffer() : buffer()
		{
#ifdef _WIN32
			ZeroMemory(this->p, this->Size);
#endif
		}
		~audio_buffer() 
		{
			if(p)
				free(this->p);
		}
	};

	class audio_format
	{
	public:
		void* info;
		audio_format(int m_nChannels = 1, int m_nSampleRate = 44100)
		{
#ifdef _WIN32

			WAVEFORMATEX waveFormat;
			waveFormat.wFormatTag = WAVE_FORMAT_PCM;
			waveFormat.nSamplesPerSec = m_nSampleRate;
			waveFormat.wBitsPerSample = sizeof(short) * 8;
			waveFormat.nChannels = m_nChannels;
			waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
			waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
			waveFormat.cbSize = 0;
			info = (void*)&waveFormat;
#endif

		}
	};
}