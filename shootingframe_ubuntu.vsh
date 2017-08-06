attribute  vec4 position;
attribute  vec2 _uv;
uniform  mat4 pvmMat;
varying  vec2 _outUV;

void main(void)
{
    vec4 pos = position;
     _outUV = _uv;
    gl_Position = pvmMat*pos;

}
