attribute vec3 position;
uniform  mat4   modelMat;
uniform  mat4   projViewMat;

void main()
{
    mat4 matix = projViewMat*modelMat;
    gl_Position = matix*vec4(position,1.0f);
}
