# minishell

description: my own custom shell coded in c for the 1337 curriculum.

## the story
building a shell from scratch is crazy. you type a command in bash and it just works, but behind the scenes, there is so much going on. i had to figure out how to break down the input with a tokenizer[cite: 1], handle weird syntax errors[cite: 1], and manage all the environment variables[cite: 1]. splitting the work between parsing the commands[cite: 1] and actually executing them[cite: 1] was a massive puzzle.

## the goal
the main objective was to make a working shell that handles all the basic built-in commands like cd, echo, env, exit, export, pwd, and unset[cite: 1]. it also needed to flawlessly support redirections and heredocs[cite: 1], string commands together with pipes[cite: 1], expand environment variables[cite: 1], and match wildcards[cite: 1]. i also added a garbage collector[cite: 1] to make sure there were zero memory leaks when the shell was running.

## the lesson
i learned so much about how the operating system actually works under the hood. managing file descriptors for redirections, handling child processes to execute commands[cite: 1], and safely catching keyboard signals[cite: 1] really leveled up my low-level c programming. putting together the execution tree and making sure all the pipes talked to each other correctly was tough but getting it working perfectly was the best feeling.

## how to use
if you want to test it out, just open the terminal in the repo and run make[cite: 1]. this will compile everything and create the minishell executable[cite: 1]. after that, just run `./minishell` and you will drop into my custom prompt where you can run commands just like normal bash.
