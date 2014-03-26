project
=======

The assembler for CSCI30000

As I mentioned on Thursday, the primary problem with making real progress is that I don't know where to start.  In its most basic form, we want a thing that takes code in the form

     0         START     0
     1         LDA       #10
     2         LDX       #0
     3    LOOP COMPR     A,X       .This program loops around ten times doing nothing else
     4         JEQ       OUT
     5         SUB       #1
     6         J         LOOP
     7    OUT  END

And turns it into a file in the form

HHello12345
Tdeadbeef
M41

At the moment, I am totally unconcerned with the object program step. I want to have a way to turn 
"LDA #10" Into "01000A".

A line of code is broken into five distinct segments, of which I only care about three.  Line numbers and comments do nothing, so the only code they merit is code to recognize and ignore them.  At the moment, assume input does not contain them.  Thus the three relevant segments are label, operator, and operand.  

Operators exist 1:1 with hex strings in a way that is fetchable from my getInstruction() function.  However, some operators are not mnemonics for opcodes at all; they're assembler directives.  In pass one, we must look at each operator and decide whether or not to process this as a directive.  Thus, we need a DB/get combo similar to the Instructions set but for directives.  Unlike the instructions, they don't all behave the same way, so the get will be a bool-returning isDirective().  A prototype of this header now exists.

Got off topic there.  Anyway, object code for instruction is easy.  Next we need flag bits, if and only if the instruction is of type 3, an effortless thing to know.  NIXBPE.  With the exception of B and P, all can be obtained by analysis of the operator and operand.  If operator[0] == '+', the operator should be trimmed of that + and e set to 1.
A leading # in operand means i=1.  Leading @ means n=1.  These are mutually exclusive.  A trailing ",X" means x=1.B and P are special cases, in that they are not spoken of by the programmer.  

We need to compute desiredTarget, aka what the programmer WANTS.  With no punctuation, the operand is a label corresponding to the address the programmer wants.  The relationship between the two will be handled by my SymbolTable during pass 1.  With #, if the chars are numbers, the operand's int value is what the programmer wants.  The programmer can use X', C', or B' as well, but I don't care about that right now.  If the chars are letters, the operand is a label to be used as a key in the LabelTable.  Still easy.
With e=1, the operand is once again exactly what the programmer wants.  With @, there's some dereferencing going on, but that's machine-level.  Code-level, we don't care.  Use operand as desired address.

So it's effortless to find what we want.  Now we need to find out what we need.  There's a Rolling Stones joke in there somewhere.  If e=1 or i=1, what we need is what we want.  If not, check if what we want is within range of where we are. operands are 12bit and thus range in [0,4095] or [-2048,2047].  Therefore, check whether:
(PC - 2048) <= what we want <= (PC + 2047).  If true, P=1 and need = (PC-want).  
If that range is false, check if BASE has been set.  This is done through an assembler directive, and is conditional to sets of lines of code, so in pass one create ranges of BaseBlocks, which contain starting points, ending points, and values.  If (a start) < current location <= (the end) and value <= want <= (value+4095), then B=1 and need = (want - value)
If none of these conditions are true, then the address is unreachable and an error message should be thrown.

The object code string is thus, in abstract:
(Operator + ("B" + 2*n + i)) + xbpe + (need.getHex())

Thus, the work that must be done to generate object strings is:
-Obtain the hex of the operator (DONE)
-Obtain the flag bits nixe based on text (DONE)
-Obtain p, b, and address based on flag bits, value of operator, current location, and state of Base. (DONE)

Well that was fun.  Now that the flag bits can be obtained, we can work on obtaining the object code itself.  FBbp() can be used to turn want into need; it returns bp but we don't *have* to use it.  However, it does need to know what we want... in the form of a number.  Labels will be handled by LabelTable, a SymbolTable.  SymbolTables use [label] to return a number.  When we see that we're dealing with a label, we can make an int, grab the label's value, and run it through FBpe.  Now we have an integer that can be turned into a Hex() and added to a string of object code.

As for the problem of turning lines into distinct segments, 362's programming assignment 2 is a very similar concept.  So similar that I'm going to overlap their solutions.  What's more, prog-ass 3 deals with sorting methods, of which I'm going to include Heap Sort, which would be useful in prog-ass 2 which would be useful here.  So I'm going to do a lot of work at once in the process of solving the line-to-blocks problem, but it might take a while.  Few days?  Don't really know yet.  Heaps are hard.

Heap wasn't that hard.  Not sure if we'll need it for this though.  Anyway, a divideString() function now exists that returns a linked list of blocks divided by a demarkation character.  Like, say, whitespace.  For now, the first block is label, the second is operand, and the third is operand.  We're going to have to think of some way to compensate for absent labels.  Maybe, if the line has 3 blocks then read as label-operator-operand and if it only has two read it as operator-operand.  Still doesn't compensate for comments, but I don't care about comments yet.

Thus, to turn a line of code into object code: divide it by whitespace, if operand is numbers roll with it, if letters grab it from the LabelTable.  Feed operator/operand into nixbpe.  Concatinate to taste and serve with a side of horseradish.  Suggested wine pairings include merlot and cabernet. 
Modes 2 and 1 are a lot simpler.  2 involved grabbing register values from a new DB I put in the Instructions header, including an annoying init function that exists to get around C++'s weirdness.  1 was nothing at all.  We now have a way to convert a line of assembly code into a line of hexidecimal with nothing more than a single function call.  It has no support for line numbers or comments, but large amounts of deal with it are forthcoming.

*WHERE TO GO FROM HERE*
The objective I had on Thursday, implement a way to turn assembly code into object code, is complete.  We can now turn our eyes to the stars and think about the assembler as a whole.  Our next big challenge is identifying and processing assembler directives.  There are a lot of those, so at first I want to just be able to identify them.

I updated most of the files to include four new C++ technologies I learned about: map, an STL template that basically is my SymbolTable, foo->bar, a way of accessing items through pointers that previously I was emulating with (*foo).bar, switches, control flow tools that previously I was emulating through if-else if-else blocks, and exception handling, which previously I was emulating by returning empty objects and/or returning strings with "!!! ERROR !!!" in them.
Functionality has not changed, but readability and professionalism has vastly improved.
