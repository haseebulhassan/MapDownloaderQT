#ifndef TILESCALC_H
#define TILESCALC_H


static class TilesCalc
{

public:
    TilesCalc();
    static void CalculateTiles();
    //static int latlon2xy(int z, double lat, double lon, int a);

   static long TotalTiles;
   static long TotalTilesLat;
    static long TotalTilesLon;
   static double TotalDiskReq;
   static int TotalTimeReq;
   static double Longitude_Start;
   static double Latitude_Start;
   static double Longitude_End;
   static double Latitude_End;
   static int zoom;

#define TileSizeBytes (64)  //kB
#define TimeReqPerTile (100) //secs
}TilesCalc;

#endif // TILESCALC_H
