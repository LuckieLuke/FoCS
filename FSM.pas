type t1 = array[0..13,0..13] of Integer;
type t2 = array[0..13,0..1] of Integer;
type t3 = array[0..13] of boolean;

var X, Y : Integer;
    tab : t1;
    wyn : t2;

// drukowanie tablicy przejść
procedure print_t1(arr : t1);
begin
  for X := 0 to 13 do
  begin
    for Y := 0 to 13 do
    begin
      write(arr[X,Y]:3);
    end;
    writeln();
  end;
end;

//drukowanie wyniku
procedure print(wyn : t2; i : integer);
begin
  writeln;
  for X := 0 to (i-1) do
  begin
    for Y := 0 to 1 do
    begin
      case (wyn[X,Y]) of
      0:
        write('CWKS-nic ');
      1:
        write('WS-CK ');
      2:
        write('CWS-K ');
      3:
        write('S-CWK ');
      4:
        write('CKS-W ');
      5:
        write('K-CWS ');
      6:
        write('W-CKS ');
      7:
        write('CWK-S ');
      8:
        write('CK-WS ');
      9:
        write('nic-CWKS ');
      10:
        write('CS-WK ');
      11:
        write('CW-KS ');
      12:
        write('WK-CS ');
      13:
        write('KS-CW ');
      end;

      if Y = 0 then
      begin
        write('-> ');
      end
      else
        writeln;
    end;
  end;
  writeln;
end;

//sprawdzanie czy wynik ma pętle
function bez_powt(wyn : t2; i : Integer) : boolean;
var test : Integer;
    spr : t3;
begin
  test := 0;
  for X := 0 to 13 do
  begin
      spr[X] := false;
  end;

  for X := 0 to (i-1) do
  begin
      if (spr[wyn[X,1]] = false) then
      begin
        spr[X] := true;
        test := test + 1;
      end;
  end;
  if (test = i) then
  begin
      bez_powt := true;
  end;
  if (test <> i) then
  begin
      bez_powt := false;
  end;
end;

//sprawdzanie, czy w wyniku są nieporządane stany
function czy_poprawne(wyn : t2; i : Integer) : boolean;
var test : Integer;
begin
  test := 0;
  for X := 0 to (i-1) do
  begin
    if (wyn[X,1] > 9) then
      test := test + 1;
  end;

  if (test = 0) then
  begin
    czy_poprawne := true;
  end
  else if (test > 0) then
  begin
    czy_poprawne := false;
  end;
end;

//rekurencyjne przechodzenie w celu znalezienia przejścia ze stanu początkowego do końcowego
procedure szukaj(arr : t1; wyn : t2; i : Integer; a : Integer);
var b : Integer;
begin
  if (wyn[i-1,1] = 9) and (czy_poprawne(wyn, i) = true) and (bez_powt(wyn, i) = true) then
  begin
    print(wyn, i);
  end
  else if (a < 14) then
  begin
    for b := 0 to 13 do
    begin
      if (wyn[i,0] = -1) and (arr[a,b] = 1) then
      begin
        wyn[i,0] := a;
        wyn[i,1] := b;
        szukaj(arr, wyn, i+1, b);
        wyn[i,0] := -1;
        wyn[i,1] := -1;
      end;
    end;
  end;
end;

//przygotowywanie tablicy przejść
procedure zrob_tab(var tab : t1);
begin
  for X := 0 to 13 do
  begin
    for Y := 0 to 13 do
      tab[X,Y] := 0;
  end;

  tab[0,1] := 1;  tab[0,12] := 1;  tab[0,13] := 1;
  tab[1,2] := 1;  tab[1,0] := 1;
  tab[2,3] := 1;  tab[2,1] := 1;  tab[2,6] := 1;
  tab[3,4] := 1;  tab[3,2] := 1;  tab[3,10] := 1;
  tab[4,5] := 1;  tab[4,3] := 1;  tab[4,13] := 1;
  tab[5,8] := 1;  tab[5,4] := 1;  tab[5,7] := 1;
  tab[6,7] := 1;  tab[6,11] := 1;  tab[6,2] := 1;
  tab[7,5] := 1;  tab[7,5] := 1;  tab[7,12] := 1;
  tab[8,9] := 1;  tab[8,5] := 1;
  tab[9,8] := 1;  tab[9,10] := 1;  tab[9,11] := 1;
  tab[10,9] := 1;  tab[10,3] := 1;
  tab[11,9] := 1;  tab[11,6] := 1;
  tab[12,0] := 1;  tab[12,7] := 1;
  tab[13,0] := 1;  tab[13,4] := 1;
end;

//przygotowywanie tablicy wynikowej
procedure zrob_wyn(var wyn : t2);
begin
  for X := 0 to 13 do
  begin
    for Y := 0 to 1 do
      wyn[X,Y] := -1;
  end;
end;

//główna część programu
begin

  zrob_tab(tab);
  zrob_wyn(wyn);
//  print_t1(tab);
  szukaj(tab, wyn, 0, 0);

end.
