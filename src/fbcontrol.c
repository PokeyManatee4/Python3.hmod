#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/mman.h> 
#include <sys/ioctl.h> 
#include <fcntl.h> 
#include <linux/fb.h> 
#include <unistd.h> 
#include <stdio.h> 

int main ( int argc , char ** argv ) {     
   int row , col , width , height , bitspp , bytespp ;      
   unsigned int * data ;  

   // Open the device 
int fd = open ( "/dev/fb0" , O_RDWR );       

   // Get information about the framebuffer 
struct fb_var_screeninfo screeninfo ;     
   ioctl ( fd , FBIOGET_VSCREENINFO , & screeninfo );  

   // Exit if color resolution is not 32 bits per pixel 
bitspp = screeninfo . bits_per_pixel ;     
   if ( bitspp != 32 ) {   
     // output error message 
printf ( "color resolution = %i bits per pixel \n " , bitspp );      
     printf ( "Please change the color depth to 32 bits per pixel \n " );
     close ( fd );
     return 1 ; // For program termination, we output a return type != 0. }  
   

   width = screen info . xres ;   
   height = screen info . years ;  
   bytespp = bitspp / 8 ; //Calculate bytes per pixel   

   // Check if the unsigned int type has the same byte size as a pixel. 
// In our case 4 bytes (32 bits), if not the program is terminated if ( sizeof ( unsigned int ) != bytespp ) {   
       
      close ( fd );
      return 1 ; 
   }

   // Get a pointer to the framebuffer memory 
data = ( unsigned int * ) mmap ( 0 , width * height * bytespp , PROT_READ | PROT_WRITE , MAP_SHARED , fd , 0 );                  

   // Write to framebuffer memory. Here pixel by pixel 
// the color 0x000000FF (blue) is set, since a pixel has the AARRGBB format for ( row = 0 ; row < height ; row ++ )   
         
     for ( col = 0 ; col < width ; col ++ )      
        data [ row * width + col ] = 0xFF ;      

   //Release pointer 
munmap ( data , width * height * bytespp );        

   // close device 
close ( fd );   
   // return value 
return 0 ;    
}
