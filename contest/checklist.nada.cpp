Before contest checklist

Compiler
   What compiler?, what version?, what options?
Judge
   What types of error are there?
   
Practice session checklist

enter scripts and set environment, if allowed
   initadd modules: a2ps
   fix .emacs: global-font-lock, show-paren
   script.cpp, contest-keys.el.cpp, contest-extras.el.cpp, etc.
test keyboard
   Layout?
test contest utilities
   Scripts and checksum
test compiler
   Is long long available?
test STL (maybe not if compiler == g++ v2.95.3)
   Run testcode that tests all known (and used) features.
test editor
   Macros?
test judge
   Is stderr checked?
   Write code to cause every type of error? (except restricted function)
   What information is in the errormessages?
test printouts
   How to print?
   How long time to print?
test checking of scoreboard
   Is it possible to print the scoreboard?

Contest checklist
   Common errors:
      Have you read the input spec?
      Have you read the output spec?
      Graph reading:
         Are the edges unidirected or bidirected?
         Can there be multiple edges between vertices, should
         redundant ones be removed (e.g. for Floyd-Warshall)?
      Data types:
         Never hesitate to use long long (if available) even if it
         "shouldn't" be necessary (because you are wrong!!!).
      Are you really sure you have read the output spec?
