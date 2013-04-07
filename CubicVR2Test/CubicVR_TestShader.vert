#version 150

//uniform mat4 matrixModelView, matrixProjection;

in vec3 vertexPosition;
//in vec3 color;

out vec3 Color;

void main()
{
    Color = vec3(1.0,1.0,1.0);
//    gl_Position = matrixProjection * matrixModelView * vec4(vertexPosition,1.0) ;
    gl_Position = vec4(vertexPosition,1.0);
}