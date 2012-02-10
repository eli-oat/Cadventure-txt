@ SAY_HI_AGAIN
> Hi, again.

@ START
>An army of zombies is approaching your house. What will you do?
- B - LEAVE FROM THE BACK DOOR - BACK_DOOR
- F - LEAVE FROM THE FRONT DOOR - FRONT_DOOR
- D - STAY AND DEFEND YOUR HOUSE - DEFEND

@ SAY_HI
> Hi!
= SAY_HI_AGAIN
> Back to SAY_HI

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
