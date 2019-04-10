/*--------------------------------------------------------------------------------------------------------------*/
/*  Program Name                                                                                                */
/*  Author: Jason Zhang                                                                                                            */
/*  Last changes datatime 2019.                                                                                 */
/*  Version 1.0                                                                                                 */

#define MAPDATAFILE "Final_Map.map"
#define OUTFILE1 "mappointinfo.dat"
#define OUTFILE2 "maplineinfo.dat"
#define OUTFILE3 "shortestpath.dat"
#define PLOTSCRIPTFILE "plotscript.plt"

#define DATALEN 1024
#define NODENUM 4000
#define PATHNUM 4000
#define MAXLENGTH 9999.0

long nodetable[NODENUM];   //store all node, old node's number  change to new node's number
double nodeX[NODENUM],nodeY[NODENUM];  //node X,Y coordinates
double distancenode[NODENUM][NODENUM]; //node diatance from A to B
int path[NODENUM][NODENUM]; //id, path from A to B
int pathtable[PATHNUM],pathfrom[PATHNUM],pathto[PATHNUM]; //link id list // a link is from one node to //another node
