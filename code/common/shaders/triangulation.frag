R"(
#version 450 core
layout (location=3) uniform int Width; // width of the image in pixels                                                    
layout (location=4) uniform int Height; // height of the image in pixels 
// the output is an image with a float for each pixel with the corresponding values of the interpolation
layout (binding = 1,r32f) uniform image2D Result_image; 

in float Color_out;

void main(void)
{
  vec4 Result_color=vec4(Color_out,0,0,1);
    
  ivec2 Pos=ivec2(gl_FragCoord.xy);
 	// save the result
  imageStore(Result_image,Pos,Result_color);  
}
)"
