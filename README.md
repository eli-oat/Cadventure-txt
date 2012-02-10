# Cadventure-txt
**Simple text adventure engine in C**

This is a small, quick and dirty program written in a single evening for [/r/dailyprogrammer's challenge #2](http://www.reddit.com/r/dailyprogrammer/comments/pjbuj/intermediate_challenge_2/)

Cadventure uses its own simple scripting language. Here's a very simple example story:

    @ START
    >An army of zombies is approaching your house. What will you do?
    - B - LEAVE FROM THE BACK DOOR - BACK_DOOR
    - F - LEAVE FROM THE FRONT DOOR - FRONT_DOOR
    - D - STAY AND DEFEND YOUR HOUSE - DEFEND

    This and any other line that doesn't start with a command symbol is a comment.
    @ BACK_DOOR
    > You exited your house from the back door. What will you do?
    - R - GO RIGHT - RIGHT
    - L - GO LEFT -  LEFT

    @ RIGHT
    = DIE

    @ LEFT
    = DIE

    @ FRONT_DOOR
    > You exited your house through the front door, the zombies are everywhere!
    = DIE

    @ DEFEND
    > How do you want to defend your home?
    - K - USE A KNIFE - KNIFE
    - S - USE A SHOTGUN - SHOTGUN

    @ KNIFE
    > The zombies are too many.
    = DIE

    @ SHOTGUN
    > You take the shotgun.
    = DIE

    @ DIE
    > You die.

Indentation is up to the user. '@' are function definitions, '>' are print statements, '=' are function calls, and '-' are option lists. An option list looks like this:
- [KEY] - [DESCRIPTION] - [FUNCTION NAME]

You can fire your favorite text editor up and start writing your text adventure game. Then, assuming you save your story as adventure.story:
    gcc Cadventure-txt.c -o cadventure
    ./cadventure adventure.story

I only wrote this in a few hours, please excuse the code ugliness.
