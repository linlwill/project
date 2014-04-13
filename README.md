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


The Great Update
================
And how great it is.  The assembler is finished*.  That's a mighty big asterix on that word, but it's no less valid for the punctuation.  Debugging has been very light, and I mean VERY light (I ran a one-instruction program through it in both extended and non-extended formats), but from what I can see it works.  If all we did from this point was fix everything and clean up the mess, our project would pass.  

_Where To Go From Here_
Fix what we've got.  At first glance it works, but I'm way too cynical to believe there aren't still bugs.

Implement Macros.  I call dibs on this.  I've got it in my head how I want to do it; I may start on it tonight, but it's not a short-term goal.

Implement Control Sections/Program Blocks.  This will require some finagling with the directive behavior and possibly the flow logic behind the object code.  Don't know yet.

Anything Else I've Forgot.  There may or may not be features I forgot about.
