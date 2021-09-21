

    #define BUFSIZE 256
    #include <openssl/engine.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h> 
     
    int main (int argc, char *argv[])
    {
    	unsigned long err = 0;
    	int rc = 0;
    	unsigned char buf[BUFSIZE] = {0,};	
     
    	/* Load the rdrand engine */
    	ENGINE_load_rdrand();
     
    	/* Acquire a handle to the engine */
    	ENGINE* eng = ENGINE_by_id("rdrand");
    	err = ERR_get_error();
    	if(NULL == eng) {
    		fprintf(stderr, "ENGINE_load_rdrand failed, err = 0x%lx\n", err);
    		exit(1); /* failed */
    	}
     
    	rc = ENGINE_init(eng);
    	err = ERR_get_error();
    	if(0 == rc) {
    		fprintf(stderr, "ENGINE_init failed, err = 0x%lx\n", err);
    		exit(1); /* failed */
    	}
     
    	/* Set the default RAND_method to the engine */
    	rc = ENGINE_set_default(eng, ENGINE_METHOD_RAND);
    	err = ERR_get_error();
    	if(0 == rc) {
    		fprintf(stderr, "ENGINE_set_default failed, err = 0x%lx\n", err);
    		exit(1); /* failed */
    	}
     
    	/* Fill Random data to buf */
    	RAND_bytes(buf, BUFSIZE);
    #ifdef DEBUG
    	for (int i= 0; i< BUFSIZE; ++i) {
                    if ( ! (i % 16) && i ) printf("\n");
                    printf("%02x ", buf[i]);
            }
            printf("\n");
    #endif
     
    	/* Seed Entropy */
    	int seedfd = open("/dev/random", O_WRONLY);
            if (seedfd < 0) {
                    printf("RDRAND: open /dev/random failed\n");
            } else {
                    if (write(seedfd, buf, BUFSIZE) == BUFSIZE) {
                            printf("Seeded kernel with %d bits\n", BUFSIZE * 8 );
                            close(seedfd);
                    }
            }
     
    	/* Cleanup */
    	ENGINE_finish(eng);
    	ENGINE_free(eng);
    	ENGINE_cleanup();
     
    	return 0;
    }

