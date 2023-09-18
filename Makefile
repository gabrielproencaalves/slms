CC = c89
CFLAGS = -Werror -Wall
.RECIPEPREFIX = >
SRCS = main.c \
       issuebook.c \
       output.c \
       searchbook.c \
       viewbook.c \
       input.c \
       csv.c

debug: CFLAGS += -g
debug: install

install: obj
>  $(CC) $(CFLAGS) ${SRCS:c=o} -o slms

obj: $(SRCS)
>  $(CC) $(CFLAGS) -c $(SRCS)

clean:
>  rm *.o \
      slms
