srcdir = src
objdir = obj
incdir = src

CFLAGS=-g -O2

objs = $(patsubst %.c,%.o,$(wildcard src/*.c)) $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))

smhasher : $(objs)
	cc $(CFLAGS)  -arch arm64 -o smhasher $(objs) -I $(incdir) -lstdc++ -v
	#-stdlib=libstdc++

obj/%.o : src/%.c
	cc $(CFLAGS) -arch arm64 -I $(incdir) -o obj/%:.o -c src/%.c

clean:
	rm $(objs)

peek:
	echo $(objs)
