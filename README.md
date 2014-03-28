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

Control flow is now a thing.  Lines of code are looked at; blocks analyzed for membership in various maps.  Line numbers are erradicated on sight and treated like they never existed.  Comments are irrelevant.  Labels are handled in one of the sneakiest tricks I've ever come up with: flow cases are only ever odd numbers.  When labels are present, their case number is even, but can thus be subtracted by (case % 2) to produce the equivilent odd number.  That same bit of modular arithmatic can then be used as a boolean to branch behavior based on presence/absence of a label.  It's beautiful.

Directives are a catch-all rather than a set pattern of behavior, so I set up a way to measure how many operands they need and gather subsequent blocks after the call, then pass them as an array to the directive processor.

The only problems left to tackle are program blocks/control sections, macros, literals (which I don't even understand), and the final step of putting it all together in an object program that the linker/loader can work with.
