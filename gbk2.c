#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

typedef struct word {
  char c;
  struct word *next;
} word_t;

word_t *head;

typedef struct rules {
  int num;
  char *rules;
} rules_t;

rules_t symbols[26];

void make_rules(char buf[], int n) {
  int i = 4;
  int len;
  int index = buf[0] - 'A';
  len = n-i;
  symbols[index].rules = malloc(sizeof(char) * len);
  while(buf[i] != '\n') {
    symbols[index].rules[i-4] = buf[i];
    i++;
  }
  symbols[index].rules[i-4] = '\0';
  i = 0;
  while(symbols[index].rules[i] != '\0') {
    if(symbols[index].rules[i] == ' ')
    symbols[index].num++;
    i++;
  }
}

void read(char buf[], int n) {
  int c, i = 0;
  while(i < n && (c = getchar()) != EOF) {
    buf[i++] = c;
    if(c == '\n') {
      make_rules(buf, i);
      i = 0;
    }
  }
}

int guess(int n) {
  return ((rand() % n) + 1);
}

word_t *make_list(int i) {
  int n = guess(symbols[i].num);
  int counter = 0;
  int pos = 0;
  while(counter != n) {
    if(symbols[i].rules[pos] == ' ')
      counter++;
    pos++;
  }
  while(symbols[i].rules[pos+1] != '\0' && symbols[i].rules[pos+1] != ' ')
    pos++;

  word_t *word = NULL;
  while(symbols[i].rules[pos] != ' ') {
    word_t *tmp = malloc(sizeof(word_t));
    tmp->c = symbols[i].rules[pos];
    tmp->next = NULL;
    if(!word)
      word = tmp;
    else {
      tmp->next = word;
      word = tmp;
    }
    pos--;
  }
  return word;
}

void make_word() {
  int i = rand() % 26;

  while(!symbols[i].rules)
    i = rand() % 26;

  head = malloc(sizeof(word_t));
  head->c = i + 'A';
  head->next = NULL;
  word_t *beg = malloc(sizeof(word_t));
  beg->c = '-';
  beg->next = head;
  head = beg;

  word_t *print = head->next;
      while(print) {
        printf("%c", print->c);
        print = print->next;
      } printf("\n");

  word_t *tmp = head;
  while(tmp) {
    if(tmp->next && (tmp->next->c < 'A' || tmp->next->c > 'Z'))
      tmp = tmp->next;
    else if(!tmp->next)
      return;
    else {
      word_t *new = make_list(tmp->next->c - 'A');
      word_t *rem;
      word_t *delete;
      if(tmp->next) {
        rem = tmp->next->next;
        delete = tmp->next;
      }
      else
        rem = NULL;

      word_t *end = new;
      while(end->next)
        end = end->next;
      end->next = rem;
      tmp->next = new;
      free(delete);

      print = head->next;
      while(print) {
        printf("%c", print->c);
        print = print->next;
      } printf("\n");
    }
  }
}

void clear_word(word_t *head) {
  if(head) {
    if(head->next)
      clear_word(head->next);
    free(head);
  }
}

void clear_rules() {
  for(int i = 0; i < 26; i++) {
    if(symbols[i].rules)
      free(symbols[i].rules);
  }
}

int main() {
  char buf[100];
  read(buf, 100);
  srand(time(0));
  make_word();
  clear_word(head);
  clear_rules();
}
