CC = c89
CFLAGS = -Werror -Wall
.RECIPEPREFIX = >

debug: CFLAGS += -g
debug: install

install: obj
>  $(CC) $(CFLAGS) main.o issuebook.o output.o \
                   searchbook.o viewbook.o input.o \
                   slms.c \
                   -o slms

obj: main.c issuebook.c output.c  searchbook.c viewbook.c input.c slms.c
>  $(CC) $(CFLAGS) -c main.c issuebook.c output.c \
                   searchbook.c viewbook.c input.c \
                   slms.c
clean:
>  rm *.o \
      slms
