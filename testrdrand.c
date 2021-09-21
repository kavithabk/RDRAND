

    #define RDRAND_SUPPORTED 1
    #define RDRAND_NOT_SUPPORTED 0
     
    #include <cpuid.h>  
    #include<stdio.h>
     
    int main()
    {
    	const unsigned int flag_RDRAND = (1 << 30);
     
    	unsigned int eax, ebx, ecx, edx;
    	__get_cpuid(1, &eax, &ebx, &ecx, &edx);
     
    	if ((ecx & flag_RDRAND) == flag_RDRAND)	
    	{
    		printf("RDRAND Instruction Supported\n");
    		return RDRAND_SUPPORTED;
    	}
    	else
    	{
    		printf("RDRAND Instruction Not Supported\n");
    		return RDRAND_NOT_SUPPORTED;
    	}
    	return 0;
    }

