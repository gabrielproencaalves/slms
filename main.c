#include "slms.h"
#include <stdio.h>
#include <string.h>
#define NCMD 6          /* Number of available commands */
#define MAXCMDLEN 6     /* Length of largest command */
#define MAXPROMPTMSG 32 /* Maximum length of prompt message */

enum CMD {
  ADD,
  REMOVE,
  MODIFY,
  SEARCH,
  BORROW,
  QUIT
};

extern char BUFFER[];

char prompt_msg[MAXPROMPTMSG] = "> ";

static char* CMDS[] = {
  "add",
  "remove",
  "modify",
  "search",
  "borrow",
  "quit",
};

int main(void)
{
  initialize();

  while (prompt(0, prompt_msg) != EOF) {
    int CMD_INDEX;

    for (CMD_INDEX = 0; CMD_INDEX < NCMD; ++CMD_INDEX) {
      if (strncmp(BUFFER, CMDS[CMD_INDEX], MAXCMDLEN) == 0)
        switch (CMD_INDEX) {
          case ADD:
            /* Add book*/
            prints("AB");
            break;
          case REMOVE:
            /* Remove book */
            prints("RB");
            break;
          case MODIFY:
            /* Modify book */
            prints("MB");
            break;
          case SEARCH:
            /* Search book */
            prints("SB");
            break;
          case BORROW:
            /* Borrow book */
            prints("BB");
            break;
          case QUIT:
            prints("Quitting...");
            /* Quit */
            return 0;
        }
    }
  }
  return 0;
}
