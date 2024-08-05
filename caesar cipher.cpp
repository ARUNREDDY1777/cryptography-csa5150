#include <stdio.h>
int main() 
{
    char text[100];
    int shift;
    printf("Enter the plaintext: ");
   scanf("%s",text);
    printf("Enter the key value : ");
    scanf("%d", &shift);
    for(int i = 0; text[i] != '\0'; ++i) 
	{
        char ch = text[i];
        if(ch >= 'a' && ch <= 'z') 
		{
            text[i] = (ch - 'a' + shift) % 26 + 'a';
        } 
		else if(ch >= 'A' && ch <= 'Z') 
		{
            text[i] = (ch - 'A' + shift) % 26 + 'A';
        }
    }
    printf("the cipher text is :  %s\n", text);
    return 0;
}
