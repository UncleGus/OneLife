Nations mod

This mod allows for controlled spawning by assigning emails to nations.
Nation names are defined in nationNames.ini with one nation name per line.
Nation memberships are defined in nationMembers.ini with each line in the
form of `example@email.com name of the nation`

Nation spawn points are defined in nation#PositionX.ini and nation#PositionY.ini
where # is the position in the nationNames.ini file, beginning, of course, at 0
on the first line.

New players will only be born to members of their own nations.

If forceEveLocation is on, nation members spawning as Eves will spawn at their
nation's location, defaulting to 0, 0 if this isn't set for their nation.
Un-nationed players will spawn at the forceEveLocation settings.

If forceEveLocation is off, all players spawning as Eve will be spawned in the
spiral pattern.