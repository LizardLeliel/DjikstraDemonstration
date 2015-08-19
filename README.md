Djikstra Demonstration
======================

Djikstra algorithm is a famous algorithm - one of the fastest for when you need to find the absolute fast path from point a to point . Many explanations and diagrams are found all over the web, and is commonly taught in discrete mathematic courses.

However, what does it look like in code? Wikipedia offers a version of it in pseudocode, but no actual code - and of just djikstra's algorithm too. How is the graph itself represented in the machine? These were the kind of questions I asked in my first semester of university, and curious for the answer.

And this project is the result of research I did at home. The program is suposed to be where, through various command prompts, you can build a graph and ask for the shortest paths between various points. It began in as a C++ project, but C++ only the way I use the "new" keyword and constructors for structs. It was done like this to give myself a sense of C programming.

I eventually reach the point where I could represent the graph in memory, and once that happened I took a break. Once I did come back, I redid the program from scratch in a new repository - and doing the program in purely C, to give myself a challange. And from there I worked on it on and off, usually giving it improvements each time I come back with new stuff I learned from elsewhere.

A lot of the project was meant for fun, although I learned many things from it, C-related and otherwise. I don't expect anyone to find a pratical application for it, besides maybe toying around with it. But I do hope someday someone will poke around it and enjoy seeing a C version of djikstra's algorithm!
