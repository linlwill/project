project
=======

The assembler for CSCI30000

These are words.  In other news, I have never used github before.


As far as translating opcodes go, there's a dumb monkey way I did in Translator.cpp, but I want to do something better.  I'm feeling hashing: ASCII capital letters range in [65,90] decimal, so since keywords are at most 4 characters, their char values concatinated would be at most 90909090, aka around 10^8.  That's big, but it could theoretically be divided against a prime number.  Could the char values be added instead of concat'd?  Let's find out.  To pegasus!

Okay, after testing, adding the chars DOES produce duplicates.  That just won't do.  However, there's at most 2, so I could make a 2D array with structs containing Instructions and give a check against it's keyword.  This is getting dumb though; my O(N) search takes at most 59 operations, and that's not a lot.

Okay, so we'll do the linear search and return an Instruction instance.  From there construction can happen.  Implementing!
