R"(
#version 450 core
layout (location=1) in vec3 Vertex;
layout (location=2) in vec3 Color;
layout (location=3) uniform int Width; // width of the image in pixels                                                    
layout (location=4) uniform int Height; // height of the image in pixels 
layout (location=5) uniform mat4 modelviewprojection;

// layout (binding = 1,r32f) uniform image2D Result_image;


out vec4 Color_out;

void main(void)
{  
  Color_out=vec4(Color,1.0);
  gl_Position=modelviewprojection*vec4(Vertex.x*float(Width-1),Vertex.y*float(Height-1),0.0,1.0);
}
)"
