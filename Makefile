CC = c89
CFLAGS = -Werror -Wall
.RECIPEPREFIX = >

install: obj
>  $(CC) $(CFLAGS) main.o issuebook.o output.o \
                   searchbook.o viewbook.o input.o \
                   -o slms

obj: main.c issuebook.c output.c  searchbook.c viewbook.c input.c
>  $(CC) $(CFLAGS) -c main.c issuebook.c output.c \
                   searchbook.c viewbook.c input.c
clean:
>  rm *.o \
      *.a \
      *.out \
      *.so \
      slms
