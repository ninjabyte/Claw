-- Simple number guessing program

var number = rand(1,100);  -- Create new variable called number and write a random number between 1 and 100 into it
var found = 0;   -- Has the value been found
var guess_no = 1;   -- Guess number
while guess_no <= 3 && found == 0   -- For loop from 1 to 3
    var guess = input_number();   -- Sample function that prompts the user to input a number
    if guess == number
        found = 1;
        print("Found!");   -- Sample function to output a string
    elseif guess < number
        print("Too low!");
        guess_no = guess_no + 1;   -- Increment number
    elseif guess > number
        print("Too high!");
        guess_no = guess_no + 1;
    end   -- End of if
end   -- End of while
