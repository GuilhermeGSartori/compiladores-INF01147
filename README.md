# compiladores-INF01147

Repository with the assignment of the Compilers discipline of the Computer Science course (UFRGS).

The assignment is divided in 7 phases.

**Phase 1)** It was developed a "token finder" using the FLEX tool to implement regex and find the possible tokens of a "C-like" language.

**Phase 2)** After parsing (lexical validation) it necessary to verify if the syntax is correct, if the tokens are set in expected sentences of the language, this was achieved by using the bison tool in this phase.

**Phase 3)** After checking if the input code syntax is in accordance with the defined grammatic, it is necessary to create an AST to store the hierarchy of the statements in the code. To run and generate the graph in a dot image, run:

./etapa3 < input1.txt > output.txt

bash output2dot.sh < output.txt > img.dot

**Phase 4)** In this phase, we are required to verify if the code semantics are correct, since the lexical verification was done and the syntax is correct, its necessary to finish with the verification of the semantics. If this is ok, then code can be generated since the code comply with the expected rules of the "C-like" language. The semantic validation is done by using a linked list (a "stack") of Hash Tables, every hash table then stores content associated to identifiers, functions and literals in its respective scope (the hash table), and with this, we can validate the semantics.



**TO DO:** 

Fix the bugs of phase 3 (fun call in expressions and comments)
