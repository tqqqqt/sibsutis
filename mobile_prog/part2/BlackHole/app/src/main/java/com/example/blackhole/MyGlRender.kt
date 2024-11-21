package com.example.blackhole

import android.content.Context
import android.opengl.GLES20
import android.opengl.GLSurfaceView
import android.opengl.Matrix
import android.util.Log
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGlRender:GLSurfaceView.Renderer {
    private var context:Context
    private lateinit var shader:MyShader
    private lateinit var my_black_hole:MyBlackHole
    private var curent_time:Float

    constructor(_context:Context){
        context=_context
        curent_time=0f
    }

    override fun onSurfaceCreated(p0: GL10?, p1: EGLConfig?) {
        GLES20.glEnable(GLES20.GL_DEPTH_TEST)
        GLES20.glHint(GLES20.GL_GENERATE_MIPMAP_HINT,GLES20.GL_NICEST)

        my_black_hole=MyBlackHole()
        shader= MyShader(vertex_shader_code,fragment_shader_code)
        shader.linkVertexBuffer(my_black_hole.vertex_buffer)
        shader.linkTime(curent_time)
    }

    override fun onSurfaceChanged(p0: GL10?, _width: Int, _height: Int) {
        GLES20.glViewport(0,0,_width,_height)
    }

    override fun onDrawFrame(p0: GL10?) {
        curent_time+=2f
        shader.linkTime(curent_time)
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT or GLES20.GL_DEPTH_BUFFER_BIT)
        GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP,0,6)
    }

    var vertex_shader_code="attribute vec3 a_vertex;"+
            "void main() {"+
            "   gl_Position = vec4(a_vertex,1.0);"+
            "}"

    var fragment_shader_code=
        "precision highp float;\n" +
            "\n" +
            "uniform float iTime;\n" +
            "\n" +
            "vec2 iResolution = vec2(1080,2131);\n" +
            "\n" +
            "//-------------------------------\n" +
            "\n" +
            "#define iterations 10\n" +
            "#define formuparam 0.57\n" +
            "\n" +
            "#define volsteps 10\n" +
            "#define stepsize 0.2\n" +
            "\n" +
            "#define zoom   1.000\n" +
            "#define tile   1.0\n" +
            "#define speed  0.0010 \n" +
            "\n" +
            "#define brightness 0.0015\n" +
            "#define darkmatter 1.00\n" +
            "#define distfading 0.710\n" +
            "#define saturation 1.0\n" +
            "\n" +
            "#define mo (2.0 * 10. - iResolution.xy) / iResolution.y\n" +
            "#define blackholeCenter vec3(time*2.,time,-2.)\n" +
            "#define blackholeRadius 1.2\n" +
            "#define blackholeIntensity 1.0\n" +
            "\n" +
            "float iSphere(vec3 ray, vec3 dir, vec3 center, float radius)\n" +
            "{\n" +
            "  vec3 rc = ray-center;\n" +
            "  float c = dot(rc, rc) - (radius*radius);\n" +
            "  float b = dot(dir, rc);\n" +
            "  float d = b*b - c;\n" +
            "  float t = -b - sqrt(abs(d));\n" +
            "  float st = step(0.0, min(t,d));\n" +
            "  return mix(-1.0, t, st);\n" +
            "}\n" +
            "\n" +
            "vec3 iPlane(vec3 ro, vec3 rd, vec3 po, vec3 pd){\n" +
            "    float d = dot(po - ro, pd) / dot(rd, pd);\n" +
            "    return d * rd + ro;\n" +
            "}\n" +
            "\n" +
            "vec3 r(vec3 v, vec2 r)//incomplete but ultrafast rotation fcn thnx to rodolphito\n" +
            "{\n" +
            "    vec4 t = sin(vec4(r, r + 1.5707963268));\n" +
            "    float g = dot(v.yz, t.yw);\n" +
            "    return vec3(v.x * t.z - g * t.x,\n" +
            "                v.y * t.w - v.z * t.y,\n" +
            "                v.x * t.x + g * t.z);\n" +
            "}\n" +
            "\n" +
            "void mainImage( out vec4 fragColor, in vec2 fragCoord )\n" +
            "{\n" +
            "  //get coords and direction\n" +
            "  vec2 uv=fragCoord.xy/iResolution.xy-.5;\n" +
            "  uv.y*=iResolution.y/iResolution.x;\n" +
            "  vec3 dir=vec3(uv*zoom,1.);\n" +
            "  float time=iTime*speed+.25;\n" +
            "\n" +
            "  //mouse rotation\n" +
            "  vec3 from=vec3(0.0, 0.0, -15.0);\n" +
            "    from = r(from, mo / 10.0);\n" +
            "    dir = r(dir, mo / 10.0);\n" +
            "  from+=blackholeCenter;\n" +
            "  \n" +
            "    vec3 nml = normalize(blackholeCenter - from);\n" +
            "    vec3 pos = iPlane(from, dir, blackholeCenter, nml);\n" +
            "    pos = blackholeCenter - pos;\n" +
            "    float intensity = dot(pos, pos);\n" +
            "    if(intensity > blackholeRadius * blackholeRadius){\n" +
            "        intensity = 1.0 / intensity;\n" +
            "      dir = mix(dir, pos * sqrt(intensity), blackholeIntensity * intensity);\n" +
            "      \n" +
            "    //volumetric rendering\n" +
            "    float s=0.1,fade=1.;\n" +
            "    vec3 v=vec3(0.);\n" +
            "    for (int r=0; r<volsteps; r++) {\n" +
            "      vec3 p=from+s*dir*.5;\n" +
            "      p = abs(vec3(tile)-mod(p,vec3(tile*2.))); // tiling fold\n" +
            "      float pa,a=pa=0.;\n" +
            "      for (int i=0; i<iterations; i++) { \n" +
            "        p=abs(p)/dot(p,p)-formuparam; // the magic formula\n" +
            "        a+=abs(length(p)-pa); // absolute sum of average change\n" +
            "        pa=length(p);\n" +
            "      }\n" +
            "      float dm=max(0.,darkmatter-a*a*.001); //dark matter\n" +
            "      a*=a*a; // add contrast\n" +
            "      if (r>6) fade*=1.-dm; // dark matter, don't render near\n" +
            "      //v+=vec3(dm,dm*.5,0.);\n" +
            "      v+=fade;\n" +
            "      v+=vec3(s,s*s,s*s*s*s)*a*brightness*fade; // coloring based on distance\n" +
            "      fade*=distfading; // distance fading\n" +
            "      s+=stepsize;\n" +
            "    }\n" +
            "    v=mix(vec3(length(v)),v,saturation); //color adjust\n" +
            "    fragColor = vec4(v*.01,1.);  \n" +
            "    }\n" +
            "    else fragColor = vec4(0.0);\n" +
            "}\n" +
            "\n" +
            "// -----------------------\n" +
            "\n" +
            "void main(){\n" +
            "    mainImage(gl_FragColor, gl_FragCoord.xy);\n" +
            "}"
}