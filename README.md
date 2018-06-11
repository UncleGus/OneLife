Water mod

This mod adds a new biome, water. It can either represent lakes or ocean, depending on
how big you make the biomes. It also generates streams that flow into the water biomes.

This mod relies on having the right data available, so it goes hand in hand with content
changes.

1) Create the stream objects
You will at least need:
 - North to South
 - West to East
 - North to East
 - North to West
 - South to East
 - South to West
 - Spring to North
 - Spring to South
 - Spring to East
 - Spring to West
 - Water spawner (not actually visually presented to the player)
The code takes flow direction into account, but this is purely aesthetic. It will only make
a difference if your West to East looks different to your East to West. If it doesn't, then
you only need to make one object for both flow directions. If flow direction does matter, you
will also need to create:
 - South to North
 - East to West
 - East to North
 - West to North
 - East to South
 - West to South
There is one more set of optional objects used where the stream merges into the body of water.
Bear in mind that the biome blend is not symmetrical; water biome on the left merging in to
land biome on the right does not look the same as water biome on the right merging in to land
biome on the left. This is why these objects are used:
 - South to Lake
 - North to Lake
 - West to Lake
 - East to Lake

2) Create the water biome in the usual way
This is done by adding a ground_#.tga file in the ground folder of the data, and by
designating at least one object to spawn in the biome, which should be the water spawner object

3) Add water.txt definition file to the ground folder
There is a blank copy of this file in the same folder as these instructions. Add the object IDs
to identify the objects that the code should use to create the streams. Remember that if flow
direction does not matter, you can use the same object ID for both directions. e.g.
waterSouthToNorth=10000
waterNorthToSouth=10000
waterBiome=# the number of the water biome
waterScale=# the scale multiplier used for the water biome (spreads the water out, see footnotes)
waterLength=# the maximum length of a stream
waterSpawnId=# the ID of the object that spawns in the water biome, used to trigger a stream
waterXToY=# the IDs of the various water objects

4) Set biome biases
You can add an offset to any biome you want, to make them more prevalent. This is mostly intended
to be used with the water biome, but you can favour any biome you wish. In the ground folder, create
a ground_#.txt containing the value (a double) that you wish to add to that biome's fractal noise
calculation. As a guide, the average value generated is about 0.45, so an offset of 0.2 is fairly
significant. See footnotes for more information about using this for the ocean.

5) Check the server output when starting the server
The water definition file is loaded in when the server starts and is not cached. You should see
a log of the IDs being used by the server for the water objects. If something has gone wrong,
these will be negative numbers. You should also see the bias value for each biome as well.

Footnote: how to use the waterScale, biomeScale and biome bias values
Each biome has a fractal noise pattern, which, if represented visually would look like a hilly plane.
The scale spreads out the hills while the bias lifts the entire plane upwards. Intersecting all these
planes results in hills from different planes peaking through in different places, which corresponds
to the dominant biome in that area. If you want to make a particular biome more prevalent, with bigger
patches, increase its bias. If you want to make it take up more room and spread out more, increase the
scale. Whenever a new biome is added, it will effectively only peak through in some places, which
results in more patches but smaller patches. To offset this, the total number of biomes increases the
overall scale used to generate the fractal maps, so the patches get bigger and are spread out over
more space. biomeScale is a global setting that scales all biomes. The default is 0.83332, which was
hardcoded, but in this mod has been pulled out to a variable read in from the water definition file.
This is because when there is an ocean biome, the other biomes need a little more space to make good
islands.

A good set of values for an ocean biome is waterScale=5, biomeScale=1.33332, and biome bias for the
water biome of 0.3

If you simply wish to add lakes, leave all of these values as default.

If you want to quickly check what these biomes look like, uncomment line 2618 of map.cpp, recompile
and run the server:
    // outputMapImage();
This will create an image of the biome generation for a small block. The width and height of the
block is defined in lines 1110 and 1111 of map.cpp:
    int w = 1000;
    int h = 1000;

If you want to reduce the number of streams spawned, create another object to spawn in the water biome
and set its mapChance according to how much you want to reduce the streams by. E.g. to spawn a quarter
of the number of streams, set the stream spawner object's mapChance to 1 and the other object's to 3
You can make the other object invisible, or have it decay to nothing after 1 second to make it
"invisible" to the player.