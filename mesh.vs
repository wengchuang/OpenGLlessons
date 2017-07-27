attribute vec3 position;
uniform   mat4 g_matModelMaxtix;
uniform   mat4 g_matViewProjMaxtix;

void main() {
    mat4 mat = g_matViewProjMaxtix*g_matModelMaxtix ;
    gl_Position =  mat*vec4(position,1.0);
}
