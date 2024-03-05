R"(
#version 450 core

layout (location=20) uniform int Num_textures;
layout (location=21) uniform vec3 Background_color;

layout (binding=0) uniform sampler2D Textures[5];

in VS_OUT
{     
  vec2 tex_coord;    
} fs_out;            
      
out vec4 frag_color; 
      
void main(void)      
{     
  vec4 Color1=vec4(Background_color,1);
  vec4 Color_texture;
  vec4 Color_texture1;
  
  for (int i=0;i<Num_textures;i++){
    Color_texture=texture(Textures[i],fs_out.tex_coord);
    if (Color_texture.w==1){
      Color1=Color_texture;
    }
  }
  frag_color=Color1;
}     
)"
