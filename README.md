# Google-Map
Cut down version of a Google Map Project

This program implements a simplified map program, with streets that are restricted to a square grid:
either west-to-east or north-to-south. Map info is read from a file. The program maintains the collection
of streets and to answer queries about the map.

Map Description
The map area is a two-dimensional grid, with each point specified by an integer pair: (east,
north). The coordinate (0,0) is the bottom left corner of the map, and the unit of distance is a “block.”
The first coordinate (east) is the number of blocks to the right of the left edge. The second coordinate
(north) is the number of blocks above the bottom edge. (Basically, “east” is the x-coordinate and
“north” is the y-coordinate). Each point coordinate must be a positive integer, but there is no maximum limit.
A street is a straight line, which must be either horizontal (west-to-east) or vertical (north-to-south). It is
specified by a name (string), the starting point, and the ending point. For a horizontal street, the starting
point is to the left -- the western-most point. For a vertical street, the starting point is the top one -- the
northern-most point.

A map is a collection of streets. Each map has a name (up to 15 characters), and the street data for a
map named “foo” is in a text file named “foo.txt”. The text file contains a line of information for each
street, consisting of the name (up to 15 characters), the starting point, and the ending point. When drawing the 
maps out, starting points are shown as open circles. Dark circles show points that are intersections of two streets.
