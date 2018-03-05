#include <unistd.h> /* XXX getopt() */

#include <stdio.h> /* fputs */
#include <stdlib.h> /* getenv(), exit() */
#include <string.h> /* strncmp() */

void assemble_obj(char *, char *, char *, char *);
void compile_obj(char *, char *, char *, char *);
void link_exe(char *, char *, char **, char *);
void archive_lib(char *, char *, char **, char *);
char *getenvd(char *, char *);
void usage(void);
int mkdep(int, char**, char *);
int make(int, char**, char *);

#define CMD_BUF_MAX 1024
char cmd_buf[CMD_BUF_MAX];

void
usage()
{
  fputs("mmk [-d] -o <target-file> <source-file> [<source-file>...]\n", stderr);
  exit(1);
}




void
assemble_obj(char *cc, char *cflags, char *source, char *target)
{
  fputs("XXX not yet implemented", stderr);
  exit(1);
}


void
compile_obj(char *cc, char *cflags, char *source, char *target)
{
  int rv;

  rv = snprintf(cmd_buf, 1024, "%s -c %s %s -o %s", cc, cflags, source, target);
  if (CMD_BUF_MAX <= rv) {
    exit(1);
  }
  puts(cmd_buf);
}


void
link_exe(char *ld, char *ldflags, char **targets, char *executable)
{
  int rv;
  int i;

  rv = snprintf(cmd_buf, 1024, "%s %s", ld, ldflags);
  if (CMD_BUF_MAX <= rv) {
    exit(1);
  }
  fputs(cmd_buf, stdout);
  for (i=0; targets[i]; i++) {
    fputs(" ", stdout);
    fputs(targets[i], stdout);
  }

  fputs(" -o ", stdout);
  puts(executable);
}


void
archive_lib(char *ar, char *arflags, char **targets, char *library)
{
  fputs("XXX not yet implemented", stderr);
  exit(1);
}


char *
getenvd(char *envvar, char *deflt)
{
  char *value;
  value = getenv(envvar);
  if (value) {
    return value;
  } else {
    return deflt;
  }
}




int
mkdep(int argc, char **argv, char *target)
{
  fputs("XXX not yet implemented", stderr);
  exit(1);
}


int
make(int argc, char **argv, char *target)
{
  int i;

  char *curr_cc;
  char *curr_ar;
  char *curr_as;
  char *curr_ld;
  char *curr_asflags;
  char *curr_arflags;
  char *curr_cflags;
  char *curr_ldflags;

  curr_arflags=getenvd("ARFLAGS", "");
  curr_asflags=getenvd("ASFLAGS", "");
  curr_cflags=getenvd("CFLAGS", "");
  curr_ldflags=getenvd("LDFLAGS", "");
  curr_ar=getenvd("AR", "ar");
  curr_as=getenvd("AS", "as");
  curr_cc=getenvd("CC", "cc");
  curr_ld=getenvd("LD", "ld");

  char** outfiles = malloc((argc+1) * sizeof(char *));
  for(i=0; i<argc; i++) {
    size_t len=strlen(argv[i]);
    outfiles[i] = malloc(len+1);
    memcpy(outfiles[i], argv[i], len+1);
    if (!strncmp(&outfiles[i][len-2], ".c", 2)) {
      outfiles[i][len-1] = 'o';
      compile_obj(curr_cc, curr_cflags, argv[i], outfiles[i]);
    } else if (!strncmp(&outfiles[i][len-2], ".s", 2)) {
      outfiles[i][len-1] = 'o';
      assemble_obj(curr_cc, curr_cflags, argv[i], outfiles[i]);
    } else {
      fputs("unknown extension", stderr);
      usage();
    }
  }
  outfiles[argc] = NULL;

  if (!strncmp("lib", target, 3)) {
    archive_lib(curr_ar, curr_arflags, outfiles, target);
  } else {
    link_exe(curr_ld, curr_ldflags, outfiles, target);
  }

  return 1;
}



enum { CMD_CLEAN, CMD_MKDEP, CMD_MAKE };

int
main(int argc, char **argv)
{
  int ch;
  char *target;
  char command;

  command='m';
  while ((ch=getopt(argc, argv, "cdmo:")) != -1) {
    switch (ch) {
    case 'c':
      command='c';  // output clean list
      break;
    case 'd':
      command='d';  // output dependencies
      break;
    case 'm':
      command='m';  // output build commands
      break;
    case 'o':
      target = optarg;
      break;
    default:
      usage();
    }
  }
  argc -= optind;
  argv += optind;

  // -o is mandatory for all modes
  if (!target) {
    fputs("parameter <target-file> is missing.", stderr);
    usage();
  }

  // command switches between build
  switch (command) {
  case 'c':
    return 1; // XXX not yet
    ;;
  case 'd':
    return mkdep(argc, argv, target);
    ;;
  case 'm':
    return make(argc, argv, target);
    ;;
  }

}
