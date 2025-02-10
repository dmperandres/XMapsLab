//LIC

#include "board.h"

//HEA

void _board::create(float Width1, float Height1, int Num_divisions1, _vertex3f Color1, std::shared_ptr<cv::Mat> Result_floats_image)
{
  _vertex3f Vertex;
  std::vector<_vertex3f> Generator_vertices;

  // for random values
  std::random_device RD;
  std::mt19937 MT(RD());
  std::uniform_real_distribution<float> Random;

  Num_divisions=Num_divisions1;

  // Check values
  if (Num_divisions<2) Num_divisions=2;


  // Clear vectors
  Vertices.clear();
  Triangles.clear();
  Vertices_normals.clear();
  Triangles_normals.clear();
  Triangles_colors.clear();
  Vertices_colors.clear();
  Vertices_texture_coordinates.clear();

  Vertices_drawarray.clear();
  Vertices_colors_drawarray.clear();
  Vertices_triangles_normals_drawarray.clear();
  Vertices_normals_drawarray.clear();
  Vertices_texture_coordinates_drawarray.clear();

  if (Width1/Height1>=1){
    // Height is smaller
    Num_vertical_divisions=Num_divisions;
    float Height_quotient=Height1/float(Num_divisions-1);
    Num_horizontal_divisions=int(roundf(Width1/Height_quotient))+1;

  }
  else{
    // Widht is smaller
    Num_horizontal_divisions=Num_divisions;
    float Width_quotient=Width1/float(Num_divisions-1);
    Num_vertical_divisions=int(roundf(Height1/Width_quotient))+1;
  }

  // Now we know the number of vertices and triangles
  int Num_vertices=Num_horizontal_divisions*Num_vertical_divisions;
  int Num_triangles=(Num_horizontal_divisions-1)*(Num_vertical_divisions-1)*2;

  Vertices.resize(Num_vertices);
  Triangles.resize(Num_triangles);
  Vertices_normals.resize(Num_vertices);
  Triangles_normals.resize(Num_triangles);
  Triangles_colors.resize(Num_triangles);
  Vertices_colors.resize(Num_vertices);
  Vertices_texture_coordinates.resize(Num_vertices);


  float s;
  float t;
  float Min_x=-Width1/2;
  float Min_y=-Height1/2;
  int Position=0;
  int Pos_x;
  int Pos_y;

  float Width_result=0;
  float Height_result=0;
  float Depth_result=0;

  if (Result_floats_image!=nullptr){
    Width_result=float(Result_floats_image->cols-1);
    Height_result=float(Result_floats_image->rows-1);
    if (Width_result>Height_result) Depth_result=Width_result/Height_factor;
    else Depth_result=Height_result/Height_factor;
  }

  // the vertices
  _vertex3f Aux;
  for (int Row=0;Row<Num_vertical_divisions;Row++){
    s=float(Row)/float(Num_vertical_divisions-1);
    Pos_y=int(roundf(Height_result*s));
    for (int Col=0;Col<Num_horizontal_divisions;Col++){
      t=float(Col)/float(Num_horizontal_divisions-1);
      Pos_x=int(roundf(Width_result*t));

      Vertices[Position].x=Width1*t+Min_x;
      Vertices[Position].z=-(Height1*s+Min_y);

      if (Result_floats_image!=nullptr){
        Vertices[Position].y=Result_floats_image->at<float>(Pos_y,Pos_x)*Depth_result;
      }
      else{
//        Vertices[Position].y=Random(MT)*Width1/50;
        Vertices[Position].y=0;
      }

      // z=0 plane
//      Vertices[Position].x=Width1*t+Min_x;
//      Vertices[Position].z=Random(MT)*Width1/50;
//      Vertices[Position].y=Height1*s+Min_y;

      Aux=Vertices[Position];

      Vertices_texture_coordinates[Position]._0=t;
      Vertices_texture_coordinates[Position]._1=s;

      Position++;
    }
  }

  // Triangles
  Position=0;
  _vertex3i Aux1;
  for (int Row=0;Row<Num_vertical_divisions-1;Row++){
    for (int Col=0;Col<Num_horizontal_divisions-1;Col++){
      // Even triangle
      Triangles[Position]._0=linear_position(Col,Row);
      Triangles[Position]._1=linear_position(Col+1,Row);
      Triangles[Position]._2=linear_position(Col,Row+1);

      Aux1=Triangles[Position];
      Position++;
      // Odd triangle
      Triangles[Position]._0=linear_position(Col+1,Row);
      Triangles[Position]._1=linear_position(Col+1,Row+1);
      Triangles[Position]._2=linear_position(Col,Row+1);

      Aux1=Triangles[Position];
      Position++;
      }
    }

  // colors
  Triangles_colors.resize(Triangles.size());
  for (unsigned int i=0;i<Triangles_colors.size();i++){
    Triangles_colors[i]=Color1;
  }

  // random colors
  _vertex3f Color;

  Vertices_colors.resize(Vertices.size());
  for (unsigned int i=0;i<Vertices_colors.size();i++){
    Color.x=Random(MT);
    Color.y=Random(MT);
    Color.z=Random(MT);
    Vertices_colors[i]=Color;
  }

  //
  compute_triangles_normals();
  compute_vertices_normals();


  // drawarrays
  //

  Vertices_drawarray.resize(Triangles.size()*3);
  Position=0;
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_drawarray[Position++]=Vertices[Triangles[i]._0];
    Vertices_drawarray[Position++]=Vertices[Triangles[i]._1];
    Vertices_drawarray[Position++]=Vertices[Triangles[i]._2];
  }

  Vertices_colors_drawarray.resize(Triangles.size()*3);
  Position=0;
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_colors_drawarray[Position++]=Vertices_colors[Triangles[i]._0];
    Vertices_colors_drawarray[Position++]=Vertices_colors[Triangles[i]._1];
    Vertices_colors_drawarray[Position++]=Vertices_colors[Triangles[i]._2];
  }

  Vertices_triangles_normals_drawarray.resize(Triangles.size()*3);
  Position=0;
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_triangles_normals_drawarray[Position++]=Triangles_normals[i];
    Vertices_triangles_normals_drawarray[Position++]=Triangles_normals[i];
    Vertices_triangles_normals_drawarray[Position++]=Triangles_normals[i];
  }

  Vertices_normals_drawarray.resize(Triangles.size()*3);
  Position=0;
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_normals_drawarray[Position++]=Vertices_normals[Triangles[i]._0];
    Vertices_normals_drawarray[Position++]=Vertices_normals[Triangles[i]._1];
    Vertices_normals_drawarray[Position++]=Vertices_normals[Triangles[i]._2];
  }

  Vertices_texture_coordinates_drawarray.resize(Triangles.size()*3);
  Position=0;
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_texture_coordinates_drawarray[Position++]=Vertices_texture_coordinates[Triangles[i]._0];
    Vertices_texture_coordinates_drawarray[Position++]=Vertices_texture_coordinates[Triangles[i]._1];
    Vertices_texture_coordinates_drawarray[Position++]=Vertices_texture_coordinates[Triangles[i]._2];
  }
}

//HEA

void _board::update_data(std::shared_ptr<cv::Mat> Result_floats_image)
{
  float s=0;
  float t=0;
  int Position=0;
  int Pos_x;
  int Pos_y;

  float Width_result=0;
  float Height_result=0;
  float Depth_result=0;

  if (Result_floats_image!=nullptr){
    Width_result=float(Result_floats_image->cols-1);
    Height_result=float(Result_floats_image->rows-1);
    if (Width_result>Height_result) Depth_result=Width_result/Height_factor;
    else Depth_result=Height_result/Height_factor;
  }

  // the vertices
  _vertex3f Aux;
  for (int Row=0;Row<Num_vertical_divisions;Row++){
    s=float(Row)/float(Num_vertical_divisions-1);
    Pos_y=int(roundf(Height_result*s));
    for (int Col=0;Col<Num_horizontal_divisions;Col++){
      t=float(Col)/float(Num_horizontal_divisions-1);
      Pos_x=int(roundf(Width_result*t));


      if (Result_floats_image!=nullptr){
        Vertices[Position].y=Result_floats_image->at<float>(Pos_y,Pos_x)*Depth_result;
      }
      else{
        Vertices[Position].y=0;
      }

      // z=0 plane
//      Vertices[Position].x=Width1*t+Min_x;
//      Vertices[Position].z=Random(MT)*Width1/50;
//      Vertices[Position].y=Height1*s+Min_y;

      Position++;
    }
  }

  // Triangles
  Position=0;
  _vertex3i Aux1;
  for (int Row=0;Row<Num_vertical_divisions-1;Row++){
    for (int Col=0;Col<Num_horizontal_divisions-1;Col++){
      // Even triangle
      Triangles[Position]._0=linear_position(Col,Row);
      Triangles[Position]._1=linear_position(Col+1,Row);
      Triangles[Position]._2=linear_position(Col,Row+1);

      Aux1=Triangles[Position];
      Position++;
      // Odd triangle
      Triangles[Position]._0=linear_position(Col+1,Row);
      Triangles[Position]._1=linear_position(Col+1,Row+1);
      Triangles[Position]._2=linear_position(Col,Row+1);

      Aux1=Triangles[Position];
      Position++;
      }
    }
  //
  compute_triangles_normals();
  compute_vertices_normals();

  // drawarrays
  //

  Vertices_drawarray.resize(Triangles.size()*3);
  Position=0;
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_drawarray[Position++]=Vertices[Triangles[i]._0];
    Vertices_drawarray[Position++]=Vertices[Triangles[i]._1];
    Vertices_drawarray[Position++]=Vertices[Triangles[i]._2];
  }

  Vertices_triangles_normals_drawarray.resize(Triangles.size()*3);
  Position=0;
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_triangles_normals_drawarray[Position++]=Triangles_normals[i];
    Vertices_triangles_normals_drawarray[Position++]=Triangles_normals[i];
    Vertices_triangles_normals_drawarray[Position++]=Triangles_normals[i];
  }

  Vertices_normals_drawarray.resize(Triangles.size()*3);
  Position=0;
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_normals_drawarray[Position++]=Vertices_normals[Triangles[i]._0];
    Vertices_normals_drawarray[Position++]=Vertices_normals[Triangles[i]._1];
    Vertices_normals_drawarray[Position++]=Vertices_normals[Triangles[i]._2];
  }
}


