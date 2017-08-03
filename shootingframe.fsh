uniform    sampler2D   _texture;
varying    vec2        _outUV;
void main(void)
{
    vec4   color   =   texture2D(_texture,_outUV);
    if(color.a < 0.1f){
        discard;
    }
    gl_FragColor   =   color;
}
