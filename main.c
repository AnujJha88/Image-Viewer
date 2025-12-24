#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct{
int w,h;
    Uint8* r,*g,*b;
}Image;

Image deepcopy(Image* src) {
    Image dest;
    dest.w = src->w;
    dest.h = src->h;

    int total_pixels = src->w * src->h;

    dest.r = (Uint8*)malloc(total_pixels);
    dest.g = (Uint8*)malloc(total_pixels);
    dest.b = (Uint8*)malloc(total_pixels);

    memcpy(dest.r, src->r, total_pixels);
    memcpy(dest.g, src->g, total_pixels);
    memcpy(dest.b, src->b, total_pixels);

    return dest;
}
void apply_grayscale(SDL_Surface* surface, Image* img){

    Uint32* pixels=(Uint32*) surface->pixels;

    for(int i=0;i<img->w*img->h;i++){
        Uint8 gray=(img->r[i]+img->g[i]+img->b[i])/3;
        pixels[i]=SDL_MapRGB(surface->format,gray,gray,gray);
    }
}

void apply_invert(SDL_Surface* surface,Image* img){
    Uint32* pixels=(Uint32*)surface->pixels;
    for(int i=0;i<img->w*img->h;i++){
        Uint8 r=255-img->r[i];
        Uint8 g=255-img->g[i];
        Uint8 b=255-img->b[i];
        pixels[i]=SDL_MapRGB(surface->format,r,g,b);
    }
}

int main(){

    FILE* in=stdin;
    char* trash=calloc(1000,sizeof(char)) ;

    int width,height;
    //fgets(s,1000,in);//reads in line by line
/// line 1 is specifier
fgets(trash,1000,in);
/// line 2 is comment
fgets(trash,1000,in);

    //basically throw all this away we dont even need it
/// line 3 is dimensions (width,height)
char* dim=calloc(1000,sizeof(char));
    fgets(dim,1000,in);
    sscanf(dim,"%d %d\n",&width,&height);
/// line 4 is max value per channel
//we ignore this as well
fgets(trash,1000,in);
free(trash);
    free(dim);
    // ok after this there is only pixel info
    //const int width=800,height=600;
printf("width=%d, height=%d \n",width,height);

    SDL_Window* window=SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);

    SDL_Surface* surface=SDL_GetWindowSurface(window);

     Image img;
    img.w=width;
    img.h=height;
    img.r=malloc(width*height);
    img.g=malloc(width*height);
    img.b=malloc(width*height);

    for(int i=0;i<width*height;i++){
        img.r[i]=(Uint8)getchar();
        img.g[i]=(Uint8)getchar();
        img.b[i]=(Uint8)getchar();
    }

    Image orig=deepcopy(&img);
//Uint32 color=0;
    //Uint32 color=SDL_MapRGB(surface->format,r,g,b);//every surface stores a format field for the PixelFormat

    //SDL_Rect pixel=(SDL_Rect){0,0,1,1};

    //Uint32* pixels=(Uint32*)surface->pixels;
    //for(int y=0;y<height;y++){
        //for(int x=0;x<width;x++){

            //Uint8 r,g,b;
         //   r=(char)getchar();
        //    g=(char) getchar();
     //       b=(char)getchar();
         //   color= SDL_MapRGB(surface->format,r,b,g);
            //pixel.x=x;
            //pixel.y=y;
            //SDL_FillRect(surface,&pixel,color);
      //      pixels[y+width*x]=color;
       // }

    //}
    //SDL_UpdateWindowSurface(window);

    SDL_Event e;
    while(SDL_WaitEvent(&e)){
        if(e.type==SDL_QUIT) break;

        if(e.type-SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                case SDLK_i:
                apply_invert(surface,&img);
                break;
                case SDLK_g:
                apply_grayscale(surface,&img);
                break;


            }
        }

        SDL_UpdateWindowSurface(window);
    }
}
