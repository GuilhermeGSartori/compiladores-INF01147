# compiladores-INF01147

Repository with the assignment of the Compilers discipline of the Computer Science course (UFRGS).

The assignment is divided in 7 phases.

**Phase 1)** It was developed a "token finder" using the FLEX tool to implement regex and find the possible tokens of a "C-like" language.

**Phase 2)** After parsing (lexical validation) it necessary to verify if the syntax is correct, if the tokens are set in expected sentences of the language, this was achieved by using the bison tool in this phase.

**Phase 3)** After checking if the input code syntax is in accordance with the defined grammatic, it is necessary to create an AST to store the hierarchy of the statements in the code. To run and generate the graph in a dot image, run:

./etapa3 < input1.txt > output.txt

bash output2dot.sh < output.txt > img.dot

**Phase 4)** In this phase, we are required to verify if the code semantics are correct, since the lexical verification was done and the syntax is correct, its necessary to finish with the verification of the semantics. If this is ok, then code can be generated since the code comply with the expected rules of the "C-like" language. The semantic validation is done by using a linked list (a "stack") of Hash Tables, every hash table then stores content associated to identifiers, functions and literals in its respective scope (the hash table), and with this, we can validate the semantics.

**Phase 5)** Now that the 3 main validations are done (lexic, syntax and semantic) and we are sure that the code was written in accordance with the defined language, we can start translating the lines of this code to the actual "machine language commands" that the high level commands of our language are supposed to easily represent/express to operate in machine level (arithmetics over registors and memory). The first step to do this and finish the "Front-End" of the compiler is to translate the code to ILOC commands. ILOC is an intermediary language that is "close enought" (an abstraction) to machine language, with a complete universal ILOC code, then we can start working in the "Back-End" to translate the universal ILOC code to specific CPU architectures and their machine languages (assembly). To run and test the ILOC code, run:

chmod u+x ilocsim.py

SIM=<path_to>/compiladores/compiladores-INF01147/src/etapa5/ilocsim.py

./etapa5 < test_5_final.txt > output.iloc

$SIM -x -t -s --data 500 --stack 1024 output.iloc

**Phase 6)** With the code fully translated to the ILOC language, now its possible to translate this universal code AND the global table from phase 4 into the assembly language of the x86_64 architecture and generate a binary code (data and code segments) with GCC after the translation. In this phase we achieved a fully operational compiler that is able to compile code from our laguange to functional x86_64 assembly that can run in any computer with a CPU of this architecture!
