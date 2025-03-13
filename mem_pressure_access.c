#include<stdio.h>
#include<stdlib.h>

#define MEMORY_SIZE_GB 7

int main(int argc, char **argv)
{

	int i, j;
        int sccss=0;
        int fail=0;

        printf("received: %d GB\n", atoi(argv[1]));

        for(;i<256*1024*atoi(argv[1]);i++)
	{
		char *ptr = (char *)malloc(4096);
		if(!ptr) 
			fail++;
		else
		{
			for(j=0;j<4090;j++)
				ptr[j]='a';
			sccss++;
		}

	}

	printf("susscess: %d, failed: %d\n", sccss, fail);
	getchar();


}
