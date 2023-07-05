R"(
#version 450 core
layout (location=1) in vec3 Vertex;
layout (location=2) in float Color;
layout (location=3) uniform int Width; // width of the image in pixels                                                    
layout (location=4) uniform int Height; // height of the image in pixels 
layout (location=5) uniform mat4 modelviewprojection;

out float Color_out;

void main(void)
{  
  Color_out=Color;
  gl_Position=modelviewprojection*vec4(Vertex,1.0);
}
)"
