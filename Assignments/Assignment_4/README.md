# BShell README
Welcome to BShell

## Installation:
To install and run the shell type:
> $ git clone https://github.com/cs100/cs100-assignment-2-bmao-and-jmura.git <br/>
> $ cd cs100-assignment-2-bmao-and-jmura <br/>
> $ make <br/>
> $ bin/rshell <br/>

## Summary
BJShell is a custom linux shell that takes in inputs from the command line and runs the command.

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

For our parsing, our algorithm involves tokenzing the input and pushing it into an input vector. This input vector would then be used to parse for connectors, parentheses, and redirection operators. After all the parsing is done, we create commands by creating a Single Command List queue and pushing ConcreteSingleCommand objects into it. A ConcreteSingleCommand object is created by using connectors and redirection operators as a divider. So for example: 
> echo a && echo b 

would generate two ConcreteSingleCommand objects, "echo a" and "echo b" with the connector "&&" as the separator.  Our algorithm would then recursively generate a tree of commands with sublists and then execute each command in terms of precedence.

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
- Using comments within parentheses causes the command to become invalid due to the fact that the ending   	parenthesis gets deleted as a result of our comment algorithm.
- Using parentheses within quotation marks will cause undefined behavior since our algorithm does not parse quotation marks.
- Using connectors within quotation marks will cause undefined behavior since our algorithm does not parse quotation marks.
- Escape codes will cause errors as we have not implemented signal handling yet.
