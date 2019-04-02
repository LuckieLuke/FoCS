#include <stdio.h>
#include <stdlib.h>

typedef struct transition {
  char dir; //L-P
  int st_from; // 2-6
  int st_to;
  char sym_from; // X, Y, B, 0, 1
  char sym_to;
} transition_t;

typedef struct control {
  int st; //aktualny stan
  int pos; //pozycja na tasmie
} control_t;

void make_delta(transition_t delta[]) {
  delta[0].dir = 'P'; delta[0].st_from = 2; delta[0].st_to = 3; delta[0].sym_from = '0'; delta[0].sym_to = 'X';
  delta[1].dir = 'P'; delta[1].st_from = 3; delta[1].st_to = 3; delta[1].sym_from = '0'; delta[1].sym_to = '0';
  delta[2].dir = 'L'; delta[2].st_from = 4; delta[2].st_to = 4; delta[2].sym_from = '0'; delta[2].sym_to = '0';
  delta[3].dir = 'L'; delta[3].st_from = 3; delta[3].st_to = 4; delta[3].sym_from = '1'; delta[3].sym_to = 'Y';
  delta[4].dir = 'P'; delta[4].st_from = 4; delta[4].st_to = 2; delta[4].sym_from = 'X'; delta[4].sym_to = 'X';
  delta[5].dir = 'P'; delta[5].st_from = 2; delta[5].st_to = 5; delta[5].sym_from = 'Y'; delta[5].sym_to = 'Y';
  delta[6].dir = 'P'; delta[6].st_from = 3; delta[6].st_to = 3; delta[6].sym_from = 'Y'; delta[6].sym_to = 'Y';
  delta[7].dir = 'L'; delta[7].st_from = 4; delta[7].st_to = 4; delta[7].sym_from = 'Y'; delta[7].sym_to = 'Y';
  delta[8].dir = 'P'; delta[8].st_from = 5; delta[8].st_to = 5; delta[8].sym_from = 'Y'; delta[8].sym_to = 'Y';
  delta[9].dir = 'P'; delta[9].st_from = 5; delta[9].st_to = 6; delta[9].sym_from = 'B'; delta[9].sym_to = 'B';
}

void read(char *tape, int n) {
  int i;
  for(i = 0; i < n; i++)
    tape[i] = 'B';

  i = 0;
  int c;
  while((c = getchar()) != EOF) {
    if(c != ' ' && c != '\n')
      tape[i++] = c;
  }
}

void print(char *tape, control_t play, int n) {
  int i, b_count = 0;
  for(i = 0; i < n && b_count < 2; i++) {
    if(tape[i] == 'B')
     b_count++;
    if(play.pos == i)
      printf("(q_%i) ", play.st-2);
    printf("%c ", tape[i]);
  }
  printf("\n");
}

int possible_move(control_t play, transition_t delta[], char *tape) {
  int n;
  for(n = 0; n < 10; n++) {
    if(play.st == delta[n].st_from && tape[play.pos] == delta[n].sym_from)
      return n;
  }
  return -1;
}

void valid(char *tape, int n) {
  int i;
  for(i = 0; i < n; i++)
    if(tape[i] != 'X' || tape[i] != 'Y' || tape[i] != 'B') {
      printf("Tasma nie zostala zaakceptowana.\n");
      return;
    }
  printf("Tasma zaakceptowana - lancuch wejsciowy jest postaci 0^n1^n.\n");
}

void make_move(control_t play, char *tape, transition_t delta[], int n) {
  int i = possible_move(play, delta, tape);
  while(play.pos >= 0 && play.pos < n && (i+1)) {
    tape[play.pos] = delta[i].sym_to;
    play.st = delta[i].st_to;
    if(delta[i].dir == 'L')
      play.pos--;
    else
      play.pos++;

    i = possible_move(play, delta, tape);
    print(tape, play, n);
  }
  printf("KONIEC RUCHOW\n");
  valid(tape, n);
}

int main() {
  int n;

  printf("Liczba znakow na tasmie: ");
  scanf("%i", &n);
  printf("Zawartosc tasmy: ");
  char *tape = malloc(sizeof(char) * 2 * n);

  transition_t delta[10];
  make_delta(delta);

  read(tape, 2*n);
  control_t play;
  play.st = 2;
  play.pos = 0;

  print(tape, play, 2*n);
  make_move(play, tape, delta, 2*n);

  free(tape);
  return 0;
}
