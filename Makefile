OBJS=bmp.o chebyshev-tst.o chebyshev.o nrutil.o

BIN=chebyshev-tst
 
LDFLAGS+=-lglut -lGL -lGLU -lm -lstdc++

INCLUDES+=-I./ 

all: $(BIN)

%.o: %.c
	@rm -f $@ 
	$(CXX) $(CFLAGS) $(INCLUDES) -g -c $< -o $@ -Wno-deprecated-declarations 

$(BIN): $(OBJS)
	$(CC) -o $@ -Wl,--whole-archive $(OBJS) -Wl,--no-whole-archive -rdynamic $(LDFLAGS) 

clean:
	for i in $(OBJS); do (if test -e "$$i"; then ( rm $$i ); fi ); done
	@rm -f $(BIN)


