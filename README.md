# minishell

my own custom shell coded in c for the 1337 curriculum.

## the story
building a shell from scratch is crazy. you type a command in bash and it just works, but behind the scenes, there is so much going on. i had to figure out how to break down the input with a tokenizer, handle weird syntax errors, and manage all the environment variables. splitting the work between parsing the commands and actually executing them was a massive puzzle.

## the goal
the main objective was to make a working shell that handles all the basic built-in commands like cd, echo, env, exit, export, pwd, and unset. it also needed to flawlessly support redirections and heredocs, string commands together with pipes, expand environment variables, and match wildcards. i also added a garbage collector to make sure there were zero memory leaks when the shell was running.

## the lesson
i learned so much about how the operating system actually works under the hood. managing file descriptors for redirections, handling child processes to execute commands, and safely catching keyboard signals really leveled up my low-level c programming. putting together the execution tree and making sure all the pipes talked to each other correctly was tough but getting it working perfectly was the best feeling.

## how to use
if you want to test it out, just open the terminal in the repo and run make. this will compile everything and create the minishell executable. after that, just run `./minishell` and you will drop into my custom prompt where you can run commands just like normal bash.
