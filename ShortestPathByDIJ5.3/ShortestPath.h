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



struct Node{
  long oldID;
  double x;
  double y;
}node[NODENUM];

struct Link{
  long oldID;
  int from,to;
}link[NODENUM];

struct Path{
  double distance;
  int route;
}path[NODENUM][NODENUM];
