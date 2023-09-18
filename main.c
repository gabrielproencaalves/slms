#include "config.h"
#include "slms.h"
#include <stdio.h>
#include <string.h>
#define NCMD 6          /* Number of available commands */
#define MAXCMDLEN 6     /* Length of largest command */

enum CMD {
  ADD,
  REMOVE,
  MODIFY,
  SEARCH,
  BORROW,
  QUIT
};

extern char BUFFER[];

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
  CSV* db = csv_open(DBPATH);

  while (prompt(0, DEFAULT_PROMPT_MSG) != EOF) {
    int CMD_INDEX;

    for (CMD_INDEX = 0; CMD_INDEX < NCMD; ++CMD_INDEX) {
      if (strncmp(BUFFER, CMDS[CMD_INDEX], MAXCMDLEN) == 0) {
        switch (CMD_INDEX) {
          case ADD:
            add_book(db);
            break;
          case REMOVE:

            break;
          case MODIFY:

            break;
          case SEARCH:

            break;
          case BORROW:

            break;
          case QUIT:
            csv_close(db);
            return 0;
            break;
        }

        break;
      }
    }
  }

  csv_close(db);
  return 0;
}
