/* KTH ACM Contest Template Library
 *
 * Game Theory/Rep Asymm/Rep Asymm Pseudo
 *
 * Pseudo-kod for repetitive asymmetric games which starts from the end
 * positions and calcs backward.
 *
 * Credit:
 *   By Erik Bernhardsson
 *   Based on Jimmy Mardell's text on the subject...
 *   Slightly Modified by David Rydh
 */

struct position{
  char win;	// vem som vinner, den som är vid draget (isf 1) eller inte (isf -1)
  mer data som behövs för att beskriva brädet...
  int nMoves; 	// hur många valmöjligheter man har kvar
}positions[antal_positioner];


#define QUEUELEN 0x10000

struct{
  ställning
}queue[QUEUELEN];

int pushPtr;
int popPtr;

int pop(*ställning){
  if(popPtr==pushPtr)
    return 0;
  *ställningen=pop...
    popPtr=(popPtr+1)%QUEUELEN;
  return 1;
}

void push(ställning){
  pusha ställningen...
    pushPtr=(pushPtr+1)%QUEUELEN;
}

int generateMoves(ställning, int *moves, int backwards){
  // en funktion som returnerar en lista med drag som går att göra
  // från en given position (pos)

  if(!backwards){
    for(varje drag man kan göra framlänges){
      if(moves)
	moves[nMoves]=den ställningen som uppkommer om man gör det draget;
      nMoves++;
    }
    return nMoves;
  }else{
    for(varje drag man kan göra baklänges){
      if(moves)
	moves[nMoves]=den ställningen som uppkommer om man
	              gör det draget baklänges;
      nMoves++;
    }
    return nMoves;
  }
}

void set((nån typ) ställning, char winning) {
  // en funktion som sätter att en viss ställning är evaluerad till något

  positions[ställning].win=winning;
  push(ställning);
}

void test(){
  // nollställ kön
  pushPtr=0;
  popPtr=0;

  // initiera listan med varje ställning
  for(alla ställningar som finns){               
    positions[ställning].willWin=UNKNOWN;

    // antalet drag man kan göra från den ställningen
    positions[ställning].nMoves=generateMoves(ställning, 0, 0);
  }

  // sätt alla positioner där man vinner till vunna
  for(alla ställningar där man vinner){
    set(ställning, 1);
    set(ställning, 1);
  }
  for(alla ställningar där man förlorar){
    set(ställning, -1);
    set(ställning, -1);
  }

  // gå igenom spelträdet
  ställning moves[massa];
  while(pop(&ställning)){
    // processa allt som ligger i kön

    // generera alla platser baklänges
    nMoves=generateMoves(ställning, moves, 1);

    if(positions[ställning].willWin==-1){
      // isåfall kommer ju alla dragen som ledde hit vara vinnande

      for(a=0;a<nMoves;a++)
	if(positions[moves[a]].willWin==UNKNOWN)
	  set(moves[a],1);
    }else{
      // man vinner, alltså minskar valmöjligheterna för draget innan.
      // Om den inte har några valmöjligheter kvar förlorar den.

      for(a=0;a<nMoves;a++)
	if( positions[moves[a]].willWin==UNKNOWN &&
	    --positions[moves[a]].nMoves==0)
	  set(moves[a],-1);
    }
  }
}
