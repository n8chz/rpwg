#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

char *table[] = {
 "aA4@",
 "bB68",
 "cC(<",
 "dD)>",
 "eE3",
 "fF",
 "gG9&",
 "hH#",
 "iI1|!",
 "jJ",
 "kK",
 "lL",
 "mM",
 "nN",
 "oO0",
 "pP?",
 "qQ",
 "rR",
 "sS5$",
 "tT+",
 "uU",
 "vV",
 "wW",
 "xX*",
 "yY",
 "zZ2%",
 "'\"`,"
};

/* translate a single letter to a similar character, or not */
char translit(int letter) {
 char *cand;
 int len, choice;

 cand = table[tolower(letter)-'a'];
 len = strlen(cand);
 choice = rand() % len;
 return cand[choice];
}

/* find and open the words file */
FILE *get_dict(int argc, char **argv) {
 FILE *test;

 if (argc > 1) {
  test = fopen(argv[1], "r");
 }
 else {
  test = fopen("/usr/share/dict/words", "r");
 }
 if (test) {
  return test;
 }
 else {
  fprintf(stderr, "Can't find dictionary file.\n");
 }
}

/* is c either an alphabetic character or an apostrophe? */
/* /usr/dict/words contains every noun and its possessive... */
int myisalpha(int c) {
 return c == '\'' ? 1 : isalpha(c);
}

/* pick a random location in the dictionary file, */
/* advance to next word boundary, */
/* then proceed to transliterate whatever word is next */
void random_word(FILE *dict, long len) {
 long test;
 int c;

 test = rand()%len;
 fseek(dict, test, SEEK_SET);
 while (!feof(dict) && myisalpha(c = getc(dict)));
 while (!feof(dict) && !myisalpha(c = getc(dict)));
 if (!feof(dict)) {
  do {
   if (c == '\'') c = 'z'+1;
   putchar(translit(c));
  } while (!feof(dict) && myisalpha(c = getc(dict))); 
  putchar('\n');
 }
 else {
  return random_word(dict, len);
 }
}

int main(int argc, char **argv) {
 time_t t;
 FILE *dict;
 long dict_size;
 int k;

 srand((unsigned) time(&t));
 dict = get_dict(argc, argv);
 fseek(dict, 0L, SEEK_END);
 dict_size = ftell(dict);

 for (k = 0; k < 24; k++) {
  random_word(dict, dict_size);
 }
}


