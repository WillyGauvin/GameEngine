$input v_normal

#include <bgfx_shader.sh>

void main()
{
    vec4 color4 = vec4(v_normal.x, v_normal.y, v_normal.z, 1);
    gl_FragColor = color4;
}
