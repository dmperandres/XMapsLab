R"(
#version 450 core                                                                         
layout (location=0) uniform int Width; // width of the image in pixels                                                    
layout (location=1) uniform int Height; // height of the image in pixels                                                    
layout (location=2) uniform int Num_textures; // num of textures/images
layout (location=3) uniform vec3 Background_color; // background color

layout (location=50) uniform int Type[10]; // type of layer
layout (location=60) uniform float Transparency[10]; // value of transparency for the layer
layout (location=70) uniform int Inversion[10]; // if there is inversion in the laer
layout (location=80) uniform int Color_mixing[10];


// IMPORTANT
// Only 8 image units are allowed

// input
layout (binding =0,rgba8ui) uniform uimage2D Textures[7];
// output
layout (binding=7,rgba8ui) uniform uimage2D Result_image;
                                 
                                 
// main 

void main(void)                                                                           
{
  // A vertex is emitted for each pixel. There are RowsxCols pixels. Now the inverse convertion is applied
  // The column
  int Pos_x=gl_VertexID % Width;
  // The row
  int Pos_y=gl_VertexID / Width;
  // the pos that will be used to scan the texture
  ivec2 Pos=ivec2(Pos_x,Pos_y);                                                           
                                                  
//   // The initial color is black
//   uvec4 Result_color=imageLoad(Textures[0],Pos);
//   uvec4 Color;
//
//   for (int i=1;i<Num_textures;i++){
// 		Color=imageLoad(Textures[i],Pos);
// 		Result_color=Result_color | Color;
//   }
//
//   // save the result
//   imageStore(Result_image,Pos,Result_color);

  // initialize to the background color
  vec4 Color1=vec4(Background_color,1);

  vec4 Color_texture;
//   vec4 Color_texture1;
//   int Mask_active=0;
//   int Mask_value=1;

  // compute the final color by composing the obtained color of each texture
  // the textures are ordered in depth, from the farthest, at 0, to the nearest, at Num_textures-1
  for (int i=0;i<Num_textures;i++){
	// get the color
	Color_texture=vec4(imageLoad(Textures[i],Pos))/255.0;

	// LAYER_TYPE_BASIC=0, LAYER_TYPE_CANNY=1, LAYER_TYPE_DOG=2, LAYER_TYPE_KANG=3, LAYER_TYPE_ELEMENT=4, LAYER_TYPE_COMPOUND=5, LAYER_TYPE_POSITIONS=6, LAYER_TYPE_KMEANS=7

	if (Type[i]>3){
		// for normal layers
		// current combination -> decal
		if (Color_mixing[i]==1){
			if (Color_texture.a!=0)	Color1=mix(Color1,Color_texture,(1-Transparency[i])*Color_texture.a);
		}
		else{
			Color1=mix(Color1,Color_texture,(1-Transparency[i])*Color_texture.a);
		}
	}
	else{
		// layers for borders and other effects
		// check that the valued is valid (remember that componet w=0 implies that is not valid
		if (Color_texture.w==1){
			if (Inversion[i]==1){
				// if there is inversion
				Color_texture=vec4(vec3(1)-vec3(Color_texture),Color_texture.a);
			}

			// compute the final result as the linear interpolation of the previous color and the current one, taking into account the transparency
			Color1=mix(Color1,Color_texture,1-Transparency[i]);
		}
	}
  }

  // save the result
  uvec4 Color1_aux=uvec4(Color1*255.0);
  imageStore(Result_image,Pos,Color1_aux);
}                                                                                         
)"
