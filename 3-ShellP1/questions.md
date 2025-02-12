1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**:  fgets() reading stops when encountered either EOF or a newline. After stopping, fgets() stores the input in the buffer with a terminating null byte ('\0').
    Since we want to read the user input line by line, fgets() would be a good choice for this application.

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  I believe the main reason we want to use `malloc()` instead of using a fixed array is so that we can prevent stack overflow error. Heap memory is larger than stack memory
    so if the user were to input something large, we can just allocate a massive amount of memory to account for that. Another reason is we can easily free the heap memory after using
    so if we don't require the buffer anymore, we can just free the memory and use the memory for other purposes.


3. In `dshlib.c`, the function `build_cmd_list(`)` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**:  The main reason we need to trim spaces is so that the shell can process the input correctly and output the processed commands accurately back to the terminal. If we didn't trim it and we compared commands, the commands that should be the same same would be different because of those extra spaces. 

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**:  Input Redirection - Our shell should be able to redirect the input from what user types into a file. I don't see that much of a challenge for input redirection since we are getting what user types from stdin and writing that input into a file.
    Output Redirection - Our shell should be able to redirect the output of command into a file. This can get complicated as there are values that are returned and there are values that are printed. We need to figure out a way to not output both of them onto the shell and redirect all the printed and returned values into a file.  
    Combined Redirection - Our shell should be able to redirect stdout and stderror to the same file. Even though this is merged, the challenge is similar to output redirection. Additionally, we have to figure out the syntaxes to do the combined redirection.
    

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**:  Redirecting is saving output and input of programs into files whereas piping is taking the output of a command to feed into another input of a command.   

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**:  The main reason to keep those seperate is to solve the semipredicate problem allowing output and errors to be distinguished. In computer programming, a semipredicate problem occurs when a subroutine intended to return a useful value can fail, but the signalling of failure uses an otherwise valid return value. The problem is that the caller of the subroutine cannot tell what the result means in this case. Therefore, it is important to keep these separate in a shell as if we were to redirect and pipe with just one stream, both the errors and output will be mixed.

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**:  This can be configured in any way the user favors. However, there is a common standard where returning a negative number means the command fails and returning a non-negative number means the command is successful. So, the user can check whether a command passes or not by typing $? to see the last return stage. Another thing our shell should do is output the error message to the terminal so that the user knows the error even when they are redirecting or piping. We also should provide a way to merge STDOUT and STDERR. I am thinking of combining special characters (E.g: >$, <$, >>$, <<$) to indicate whether we want to include headers like "output" and "error" to differentiate them. The users can also drop $ to make our shell behave like any linux shell would and they can use & to redirect merged outputs to files.