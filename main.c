#include <stdio.h>
#include <Windows.h>

//6	0x36	6 key
//7	0x37	7 key

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


