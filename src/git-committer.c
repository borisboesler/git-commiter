/*
 * Project:     git-committer
 * File name:   git-committer.c
 * Purpose:     create git commands to populate a git repository
 * Author:      Boris Boesler
 * Modified by:
 * Created:     13.06.2021
 * Copyright:   (c) 2021 Boris Boesler
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "git-committer-version.h"


// name of file that will be modified and commited, but must have been
// added previously
static const char* FileName = "modified-content.txt";

// different git commit messages
static const char* GitOptions[] = {
  " -m \"feat(chglog): Subject %s\"",
  " -m \"Body %s\"",
  " -m \"Body @John-Doe-%s\"",
  " -m \"Signed-off-by: Name Sign Offer <signer@signer-net-%s.com>\"",
  " -m \"Co-authored-by: Name Co Author <coauthor@author-net-%s.com>\"",
  " -m \"Closes #%s\"",
  " -m \"BREAKING CHANGE: %s\""
};


// number of different git commit messages
static const unsigned NumEntries = sizeof(GitOptions) / sizeof(const char*);


// print a version
static void showVersion()
{
  printf("git-committer version: %d.%d.%d\n",
	 GIT_COMMITTER_VERSION_MAJOR,
	 GIT_COMMITTER_VERSION_MINOR,
	 GIT_COMMITTER_VERSION_PATCH);
}


// emit value n as binary into buffer
static void getBinary(int n, char *Buffer)
{
  unsigned i = 0;
  while (n) {
    Buffer[i] = (n & 1) ? '1': '0';
    n >>= 1;
    ++i;
  }
  Buffer[i] = '\0';
}


// unfold a pattern to multiple git commands
static void handlePattern(unsigned Value)
{
  char Buffer[32];
  getBinary(Value, Buffer);
  printf("echo \"%s\" >> %s; git commit -a", Buffer, FileName);

  unsigned Shifted = 0;
  while (0 < Value) {
    if (Value & 1) {
      printf(GitOptions[Shifted], Buffer);
    }
    Value >>= 1;
    ++Shifted;
  }
  printf("\n");
}


// long options
static struct option longOptions[] = {
  { "version", no_argument, 0,  0 },
  // end marker
  { 0,         0,           0,  0 }
};


// main routine
int main(int argc, char **argv)
{
  int c;

  // analyse args
  while (1) {
    int option_index = 0;

    c = getopt_long(argc, argv, "", longOptions, &option_index);
    if (c == -1) {
      break;
    }

    switch (c) {
    case 0:
      switch (option_index) {
      default:
	break;
      case 0: // version
	showVersion();
	exit(EXIT_SUCCESS);
	break;
      }

      break;
    }
  }

  if (optind < argc) {
    printf("non-option ARGV-elements: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);
    printf("\n");
  }

  // enumerte all patterns, keep bit 0 = 1
  for (unsigned i = 1, end = (1 << NumEntries) - 1; i <= end; i+=2) {
    handlePattern(i);
  }

  return EXIT_SUCCESS;
}
