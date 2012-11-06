// Ex 6.9: counting thingies

#include "../Ch6headers.h"

int main()
{
	const char *c = "This is an example string. \nIt contains both vowels and the other things. A-cheers!";

	int aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0, otherCnt = 0;
	int whitespaceCnt = 0, hXCnt = 0;
	while (*c)
	{
		switch (*c)
		{
			case 'a': case 'A':
				aCnt++;
				break;
			case 'e': case 'E':
				eCnt++;
				break;
			case 'i': case 'I':
				iCnt++;
				break;
			case 'o': case 'O':
				oCnt++;
				break;
			case 'u': case 'U':
				uCnt++;
				break;
			case ' ': case '\t': case '\n':
				whitespaceCnt++;
				break;
			case 'h':
				{
					switch (*(c+1)) 
					{
						case 'e': case 'l': case 'h':
							hXCnt++;
							break;
						default:
							break;
					}
				}
			default:
				otherCnt++;
				break;
		}
		c++;
	}

	cout << "A: " << aCnt << ", E: " << eCnt << ", I: " << iCnt << ", O: " << oCnt << ", U: " << uCnt << endl;
	cout << "Whitespace: " << whitespaceCnt << ", Other letters: " << otherCnt << endl;
	cout << "he/hl/hh: " << hXCnt << endl;

	return 0;
}
