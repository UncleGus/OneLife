Restraint mod

This mod adds the ability to define stunning weapons. These weapons, when used against
a player, put them into a hidden "stunned" state which has no effect in itself. However,
if a second player then uses a stunning weapon on an already stunned player, the player
will be killed or incapacitated, depending on a server setting. The second stun action
must be by a different player, so this can only be utilised by more than one person.
The intention is to make it easier to overpower solo griefers.

There are two variables set in server/settings:

stunTime: (default 20) the amount of time a player will be in the hidden stunned state
or the incapacitated stun state.

killOnStun: (default 0) if this is 1, instead of being incapacitated on second stun,
the player will be killed.

To define an object as a stunning weapon, give it the property stunDistance, e.g.

stunDistance=1