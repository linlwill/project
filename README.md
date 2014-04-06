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

Literals: I don't understand these.  They allow the direct use of relative address instead of a label; that use is supported as-is because if the object code generator sees numbers it passes them as-is.  Research is needed.

Memory management: The programmer can set aside blocks of memory, and optionally intialize them to some value.  This one will be easy; upon seeing it increment the current location by that many blocks, thus passing over those spaces.  For an intialized value, on pass two when code is being written, throw that value into the space.  This might prove hazardous; don't know yet.

Expressions: I'm not sure the cannonicality of this, but I want the programmer to be able to use simple math in operands.  /*+- are good.  When encountered, they form a quick parsing tree, grabbing the block to their immediate left and right.  Since * can mean "multiply" or "current location", do some context-sensative stuff.  If *'s children are math operators or nothing, handle as current location.  If it is bookended by labels or numbers, multiply.

And, of course, the ultimate problem: object code.


Right now, I actually want to get object code working.  Right now, at this moment, I have made everything we need to make a low-functioning assembler.  No fancy macros, control sections, memory, etc, but it can translate basic code.  That's good enough for me.  Higher functions act on object code so we'd be starting from a lower point anyway.  So, right now, at this moment, I am going to solve the problem of object code.  Then other functions can emerge.
