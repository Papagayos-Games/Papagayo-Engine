#include "windows.h" 
#include "fmod.h" 
#include "fmod_errors.h" 
#include ".\sound.h"

class Sound
{
public:
	Sound(char *fname);
	~Sound(void);
	void createScene(float pos[]);
	void Sound::play();
	void Sound::stop() ;
};



FSOUND_SAMPLE *sample; 
char *filename; 
int m_channel; 


Sound::Sound(char *fname) 
{ 
   sample = 0; 
	//sample = NULL; 
   filename = fname; 
} 

Sound::~Sound(void) 
{ 
   if(sample != 0) 
      FSOUND_Sample_Free(sample); 
} 

void Sound::createScene(float pos[]) 
{ 
   float vel[3] = { 0,0,0 }; 
   int num2d, num3d; 

   if((sample = FSOUND_Sample_Load(FSOUND_FREE, filename, FSOUND_HW3D, 0, 0)) == 0) 
   { 
     MessageBox( NULL, NULL, "bad wav file name!", MB_OK | MB_ICONERROR | MB_TASKMODAL ); 
   } 

   FSOUND_Sample_SetMinMaxDistance(sample, 4.0f, 10000.0f);    
   FSOUND_Sample_SetMode(sample, FSOUND_LOOP_NORMAL); 

   m_channel = FSOUND_PlaySoundEx(FSOUND_FREE, sample, 0, true); 
   FSOUND_3D_SetAttributes(m_channel, pos, vel); 

   FSOUND_GetNumHWChannels(&num2d, &num3d, 0); 
} 

void Sound::play() 
{ 
   //FSOUND_SetPaused(m_channel, FALSE); 
   FSOUND_SetPaused(m_channel, false);
} 

void Sound::stop() 
{ 
   //FSOUND_SetPaused(m_channel, TRUE); 
	FSOUND_SetPaused(m_channel, true); 
} 

void Sound::createScene(Ogre::Vector3 vec)
{ 
    int pos[] = { vec[0], vec[1], vec[2] };
    createScene(pos);
}