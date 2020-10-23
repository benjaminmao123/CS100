# BShell README
Welcome to RShell

## Installation:
To install and run the shell type:
> $ git clone https://github.com/benjaminmao123/CS100.git <br/>
> $ cd Assignments/Assignment_4 <br/>
> $ make <br/>
> $ bin/rshell <br/>

## Summary
RShell is a custom linux shell that takes in inputs from the command line and runs the command.

Our current implementation supports the commands:
- **Connectors:** 
    - ";"
    - "&&"
    - "||"
- **Precedence Operators:**
    - "("
    - ")"
- **Redirection:** 
    - "|" 
    - "<" 
    - ">" 
    - ">>"
- **Built-in Commands:** 
    - "exit"
    - "cd"
    - "test"
        - For the test built-in command, we support the bracket notation as well e.g. "[ -e src/main.cpp ]"

For our parsing, we first tokenized the input into a vector of strings and then converted them into Command token objects.
We then run shunting yard on the tokens to create a vector of postfix tokens. This vector is then converted into reverse polish notation.
The output is a nested command that is run by our executor.

So for example 
> echo a && echo b | tr A-Z a-z > test.txt && cat < test.txt 

would look like:
> Root: "|" <br/>
> Root->lhs: "&&" <br/>
> Root->lhs->lhs: "echo a" <br/>
> Root->lhs->rhs: "echo b" <br/>
> Root->rhs: "&&" <br/>
> Root->rhs->lhs: ">" <br/>
> Root->rhs->rhs: "<" <br/>
> Root->rhs->lhs->lhs: "tr A-Z a-z" <br/>
> Root->rhs->lhs->rhs: "test.txt" <br/>
> Root->rhs->rhs->lhs: "cat" <br/>
> Root->rhs->rhs->rhs: "test.txt" <br/>

## Tasks Distribution:
- **Tasks**
	- Task 1: Github Setup (10%)
	- Task 2: Input redirection (For commands contain "<", 20%)
	- Task 3: output redirection (For commands contain ">" and ">>", 20%)
	- Task 4: Piping (25%)
	- Task 5: construct test scripts (enough test cases, 15%)
	- Task 6: construct json and README files, and git commit (10%) 

- **Benjamin Mao Complete:**
	- Task 1: Github Setup (10%)
	- Task 2: Input redirection (For commands contain "<", 20%)
	- Task 3: output redirection (For commands contain ">" and ">>", 20%)
	- Task 4: Piping (25%)
	- Task 5: construct test scripts (enough test cases, 15%) <br/>
	- Task 6: construct json and README files, and git commit (10%) <br/>
	**Total: 100%**
	
## Known Bugs
- Using parentheses within quotation marks will cause undefined behavior since our algorithm does not parse quotation marks.
- Using connectors within quotation marks will cause undefined behavior since our algorithm does not parse quotation marks.
- Escape codes will cause errors as we have not implemented signal handling yet.
