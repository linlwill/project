project
=======

The assembler for CSCI30000

The goal is to turn this:

     0         START     0
     1         LDA       #10
     2         LDX       #0
     3    LOOP COMPR     A,X       .This program loops around ten times doing nothing else
     4         JEQ       OUT
     5         SUB       #1
     6         J         LOOP
     7    OUT  END

into this:

     HHello12345
     Tdeadbeef
     M41

And I'm getting close to making it.

At the moment, I can identify the following unsolved problems:

Program blocks - allow the programmer to write code in multiple files with directives given to publish/include material between said files.  During assembly, all the files are treated as the same.

Macros - by bookending a block of code with directives, the label of the first line can be used as an instruction to insert the bookended code.
     Subtask: permit variables to be passed.
     Subtask: branch outputed code based on state of variables (or other conditionals)
     Subtask: implement dynamic renaming of instance-labels.  Invoking a macro that includes the label "Pie" will create the label "APie".  Another invocation will create the label "BPie".

Memory Management: this has been implemented.  Wasn't very hard.

Literals: Textbook makes these more complicated than they need to be.  If given an = as a leading flag in opand, run it literally.  No need for the textbook's temporary label nonsense.  This has been implemented (I think)

Expressions: I'm not sure the cannonicality of this, but I want the programmer to be able to use simple math in operands.  /*+- are good.  When encountered, they form a quick parsing tree, grabbing the block to their immediate left and right.  Since * can mean "multiply" or "current location", do some context-sensative stuff.  If *'s children are math operators or nothing, handle as current location.  If it is bookended by labels or numbers, multiply.

And, of course, the ultimate problem: object code.


As for that ultimate problem, I've made a step forward as to it.  The program now throws object code into an out.o file as it generates it.  RES* instructions pass a newline and a T, indicating a break and a new text record.  Modification records, header records, Stone Temple Pilot records, etc are not yet implemented.
