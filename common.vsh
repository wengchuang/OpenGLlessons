attribute vec3 position;
uniform  mat4   pvmMat;

void main()
{
    gl_Position = pvmMat*vec4(position,1.0f);
}
