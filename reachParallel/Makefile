TARGETS    = reach
DEPS       = 
SNETC	   = snetc
SNETCFLAGS = -v1 -g -O3 -lm -q -distrib nodist -threading front
CLEANS     = 
CFLAGS     = -Wall -g -O3 

targets: $(TARGETS)

reach: reach.snet boxes.o basicStructures.o collinearIntersection.o compare.o cycle.o det.o distance.o escape.o findRegionOrEdge.o findXorY.o immediateReachability.o intervalRange.o  minmax.o reachability.o sort.o
	$(SNETC) $(SNETCFLAGS) $^ -lrt -o $@

boxes.o: boxes.c
	$(CC) $(CFLAGS) -c -I$(SNET_INCLUDES) $<

basicStructures.o: basicStructures.c
	$(CC) $(CFLAGS) -c $<

collinearIntersection.o: collinearIntersection.c
	$(CC) $(CFLAGS) -c $<

compare.o: compare.c
	$(CC) $(CFLAGS) -c $<

cycle.o: cycle.c
	$(CC) $(CFLAGS) -c $<

det.o: det.c
	$(CC) $(CFLAGS) -c $<

distance.o: distance.c
	$(CC) $(CFLAGS) -c $<

escape.o: escape.c
	$(CC) $(CFLAGS) -c $<

findRegionOrEdge.o: findRegionOrEdge.c
	$(CC) $(CFLAGS) -c $<

findXorY.o: findXorY.c
	$(CC) $(CFLAGS) -c $<

minmax.o: minmax.c
	$(CC) $(CFLAGS) -c $<

immediateReachability.o: immediateReachability.c
	$(CC) $(CFLAGS) -c $<

intervalRange.o: intervalRange.c
	$(CC) $(CFLAGS) -c $<

reachability.o: reachability.c
	$(CC) $(CFLAGS) -c $<

sort.o: sort.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(RMFLAGS) -- *.o *.a *.lo *.la *.Plo $(TARGETS) core vgcore.*
	$(RM) $(RMFLAGS) -- $(patsubst %.snet,%.[ch],reach.snet)

