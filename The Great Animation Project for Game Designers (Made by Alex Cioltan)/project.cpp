#include<cstdio>
#include<cstring>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
int Frames,FPS;
char Prefix[1000];
SDL_Surface *images[10000],*screen;
Uint8 *keystates=SDL_GetKeyState(NULL);
void Initialize()
{
 FILE *fin=fopen("settings.txt","r");
 fscanf(fin,"%d %d ",&Frames,&FPS);
 fscanf(fin,"%s ",&Prefix);
 fclose(fin);
 FILE *fout=fopen("errors.txt","w");
 fprintf(fout,"1\n");
 int Prefix_Lenght=strlen(Prefix);
 char v[10];
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 for(int i=1;i<=Frames;i++)
     {
      strcpy(v,Prefix);
      int c=i,j=0;
      char aux[10];
      while(c!=0)
            {
             j++;
             aux[j]=c%10;
             c/=10;
            }
      while(j>0)
            {
             v[Prefix_Lenght+c]=aux[j]+'0';
             j--;
             c++;
            }
	 c+=Prefix_Lenght-1;
	 v[c+1]='.';
	 v[c+2]='b';
	 v[c+3]='m';
	 v[c+4]='p';
	 fprintf(fout,"%s\n%s\n",aux,v);
      images[i]=SDL_LoadBMP(v);
     }
}
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
 SDL_Rect offset;
 offset.x=x;
 offset.y=y;
 SDL_BlitSurface(source,NULL,destination,&offset);
 SDL_Flip(screen);
}
int main( int argc, char* args[] )
{
 SDL_Init(SDL_INIT_EVERYTHING);
 screen=SDL_SetVideoMode(0,0,32,SDL_SWSURFACE);
 Initialize();
 int ActualFrame=0;
 while(keystates[SDLK_ESCAPE]==0 && keystates[SDLK_RETURN]==0)
	  {
	   if(keystates[SDLK_LEFT]==1)
		 ActualFrame--;
	   if(keystates[SDLK_RIGHT]==1)
		 ActualFrame++;
	   if(keystates[SDLK_SPACE]==0)
	      {
	       ActualFrame++;
	      }
	   if(ActualFrame>Frames)
		 ActualFrame=1;
	   if(ActualFrame<1)
		 ActualFrame=Frames;
	   apply_surface(0,0,images[ActualFrame],screen);
	   SDL_Delay(100*FPS);
	   SDL_PumpEvents();
	  }
return 0;
}
