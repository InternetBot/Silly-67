#include <stdio.h>
#include <Windows.h>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h" //https://github.com/mackron/miniaudio real hero right here !
#include "67.h"

//6	0x36	6 key
//7	0x37	7 key


void play_67(void){
	ma_engine engine;
	ma_result result;

	result = ma_engine_init(NULL, &engine);
	if(result != MA_SUCCESS){
		printf("we f'ed up \n");
		return;
	}

	//decoder
	ma_decoder decoder;
	if(ma_decoder_init_memory(__67_SQlv2Xv_mp3, __67_SQlv2Xv_mp3_len, NULL, &decoder) != MA_SUCCESS){
		printf("failed to decode \n");
		ma_engine_uninit(&engine);
		return;
	}
	
	ma_sound sound;
	ma_sound_init_from_data_source(&engine, &decoder, 0, NULL, &sound);
	ma_sound_start(&sound);
	
	while(ma_sound_is_playing(&sound)){
		ma_sleep(100);
	}

	ma_sound_uninit(&sound);
	ma_decoder_uninit(&decoder);
	ma_engine_uninit(&engine);
	
}

int main()
{

static int lastKey = 0;

    do
    {
        for (INT vKey = 8; vKey < 256; vKey++)
        {
// lsb for released 
            if (GetAsyncKeyState(vKey) & 0x01)
            {
                printf("Key Pressed:\n"
                       " - Virtual Key: 0x%x\n"
                       " - Scan Code : 0x%x\n",
                       vKey, MapVirtualKeyW(vKey, MAPVK_VK_TO_VSC));

				if (lastKey == '6' && vKey == '7'){
					printf("found 67\n");
					play_67();
				}

				lastKey = vKey;
            }

            Sleep(50);
        }   
    } while (TRUE);   

    return 0;
}   
	
	/*bool bIsSixPressed = false;
	

	if (GetAsyncKeyState('6') & 0x36){
		bIsSixPressed = true;
		printf("6 is pressed ....\n");
		sleep(200);
		}

	if (GetAsyncKeyState('7') & 0x37){
		printf("7 is pressed ....\n");
		bIsSixPressed = false;
		sleep(200);
		}

	for (int virtualKey = 1; virtual
			


		
	}*/


