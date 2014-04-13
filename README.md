The Great Update
================
And how great it is.  The assembler is finished*.  That's a mighty big asterix on that word, but it's no less valid for the punctuation.  Debugging has been very light, and I mean VERY light (I ran a one-instruction program through it in both extended and non-extended formats), but from what I can see it works.  If all we did from this point was fix everything and clean up the mess, our project would pass.  

What I Did
----------

Besides fixing innumerable issues, main now passes object code to a text-record handler.  It adds it to a running buffer and waits for a signal to stop: "!END!".  When that happens, it constructs texts records according to the format in the textbook and loads them into a queue.

Meanwhile in ~~the Hall of Justice~~ flag bits, the function that calculates e will now generate modification records when it's doing its final pass by passing info to a modification record handler, which loads them into another queue.  

Before Pass Two begins, the assembler generates the header record based on information gathered by START and END in Pass One.  Then it analyzes all the lines.  Then it passes one last end command to the text records and then pulls all of them off of their queue, writing them to the file.  Then it does the same thing for the modification records.  Then it generates and writes the end record.

There's also been more small, bug-fixing changes than I can count, and definitely more than I remember.  Most notibly, a few things have been moved to primary that weren't there before, DivideString() has been changed to suport tabs, line length returns the correct values (it was returning bits, not bytes), LineCase works properly (I had my odds and evens reversed) and a lot of other stuff.  Anything edited with the remark "The Great Update" was modified.

Where To Go From Here
---------------------

Fix what we've got.  At first glance it works, but I'm way too cynical to believe there aren't still bugs.

Implement Macros.  I call dibs on this.  I've got it in my head how I want to do it; I may start on it tonight, but it's not a short-term goal.

Implement Control Sections/Program Blocks.  This will require some finagling with the directive behavior and possibly the flow logic behind the object code.  Don't know yet.

Anything Else I've Forgot.  There may or may not be features I forgot about.
