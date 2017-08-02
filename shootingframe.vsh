attribute vec3 position;
attribute vec2 _uv;
uniform  mat4   pvmMat;
varying  vec2 _outUV;

void main()
{
    gl_Position = pvmMat*vec4(position,1.0f);
    _outUV = _uv;
}
