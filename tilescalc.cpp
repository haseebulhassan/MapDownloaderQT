#include "tilescalc.h"
#include <math.h>
#include <mainwindow.h>


long TilesCalc::TotalTiles=0;
long TilesCalc::TotalTilesLat=0;
long TilesCalc::TotalTilesLon=0;
double TilesCalc::TotalDiskReq=0;
int TilesCalc::TotalTimeReq=0;
double TilesCalc::Longitude_Start=0;
double TilesCalc::Latitude_Start=0;
double TilesCalc::Longitude_End=0;
double TilesCalc::Latitude_End=0;
int TilesCalc::zoom=0;


TilesCalc::TilesCalc()
{

}


double latlon2px(int z,double lat, double lon, int a)
{
    double x = 0;//2**z*(lon+180)/360*256;
    double y = 0;//-(.5*log((1+sin(radians(lat)))/(1-sin(radians(lat))))/pi-1)*256*2**(z-1);
    if (a==0) return x;
    else return y;

}


int latlon2xy(int z, double lat, double lon, int a)
{
    double xx = latlon2px(z,lat,lon,0);
    double yy = latlon2px(z,lat,lon,1);
    int x = int(xx/256);
    int y = int(yy/256);
    if (a==0) return x;
    else return y;
}

int calculate_tiles(int zoom, double lat_start, double lat_stop, double lon_start, double lon_stop)
{
    int start_x = latlon2xy(zoom, lat_start, lon_start,0);
    int start_y = latlon2xy(zoom, lat_start, lon_start,1);

    int stop_x = latlon2xy(zoom, lat_stop, lon_stop,0);
    int stop_y = latlon2xy(zoom, lat_stop, lon_stop,1);

    int total = (stop_x-start_x )*(-stop_y+start_y );

    return total;

}

void TilesCalc::CalculateTiles()
{
     int start_x = latlon2xy(TilesCalc::zoom, TilesCalc::Latitude_Start, TilesCalc::Longitude_Start,0);
    int start_y = latlon2xy(TilesCalc::zoom, TilesCalc::Latitude_Start, TilesCalc::Longitude_Start,1);

    int stop_x = latlon2xy(TilesCalc::zoom, TilesCalc::Latitude_End, TilesCalc::Longitude_End,0);
    int stop_y = latlon2xy(TilesCalc::zoom, TilesCalc::Latitude_End, TilesCalc::Longitude_End,1);

     TilesCalc::TotalTiles = (stop_x-start_x )*(-stop_y+start_y );
     TilesCalc::TotalTilesLat = (-stop_y+start_y );
    TilesCalc::TotalTilesLon = (stop_x-start_x );
    TilesCalc::TotalDiskReq = (TilesCalc::TotalTiles* TileSizeBytes)/1024;
    TilesCalc::TotalTimeReq = (TilesCalc::TotalTiles * TimeReqPerTile)/60;


}

void download_tiles(int zoom, double lat_start, double lat_stop, double lon_start, double lon_stop)
{
    int start_x = latlon2xy(zoom, lat_start, lon_start,0);
    int start_y = latlon2xy(zoom, lat_start, lon_start,1);

    int stop_x = latlon2xy(zoom, lat_stop, lon_stop,0);
    int stop_y = latlon2xy(zoom, lat_stop, lon_stop,0);

    for (int x=start_x; x<=stop_x; x++)
    {
        for (int y=start_y; y<=stop_y; y++)
        {
            //QString urll = "http://mt1.google.com/vt/lyrs=y&x=%d&y=%d&z=%d" % (x,y,zoom);
            //QString filenamee = "%d/gh_%d_%d_%d.jpg" % (zoom,x, y,zoom);
        }
    }
}
