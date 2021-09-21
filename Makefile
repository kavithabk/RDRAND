

    CC=cc
    CFLAGS=-g -Wall
    LDFLAGS=-lcrypto
    RDRAND_ENGINE=rdrand_engine
    TESTRDRAND=testrdrand
    TARGET_BINS=$(RDRAND_ENGINE) $(TESTRDRAND)
     
    %.o: %.c
    	$(CC) $(CFLAGS) -c $<
    all: $(TARGET_BINS)
     
    $(RDRAND_ENGINE): $(RDRAND_ENGINE).o
    	$(CC) -o $(RDRAND_ENGINE) $(RDRAND_ENGINE).o $(LDFLAGS)
     
    $(TESTRDRAND): $(TESTRDRAND).o
    	$(CC) -o $(TESTRDRAND) $(TESTRDRAND).o
     
    clean:
    	rm -f *.o $(RDRAND_ENGINE) $(TESTRDRAND)

