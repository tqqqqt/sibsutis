package com.example.kurswork

import android.content.Context
import android.opengl.GLES20
import android.opengl.GLSurfaceView
import android.opengl.Matrix
import android.util.Log
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10
import javax.microedition.khronos.opengles.GL10.GL_ALPHA_TEST
import javax.microedition.khronos.opengles.GL10.GL_BLEND
import javax.microedition.khronos.opengles.GL10.GL_CULL_FACE
import javax.microedition.khronos.opengles.GL10.GL_DEPTH_TEST
import javax.microedition.khronos.opengles.GL10.GL_MULTISAMPLE

class MyRender: GLSurfaceView.Renderer {
    private var context: Context
    private lateinit var shader: Array<MyShader>
    private var shaders_mas:MyShadersCodes

    private var x_camera:Float
    private var y_camera:Float
    private var z_camera:Float
    private var x_light:Float
    private var y_light:Float
    private var z_light:Float
    private var modelMatrix:FloatArray
    private var viewMatrix:FloatArray
    private var modelViewMatrix:FloatArray
    private var projectionMatrix:FloatArray
    private var modelViewProjectionMatrix:FloatArray

    private lateinit var my_table:MyTable
    private lateinit var sphere:Array<MyShpere>
    private lateinit var glass:MyGlass
    private lateinit var glass_water:MyGlass
    private lateinit var candle: MyCandle
    private lateinit var fire:MyFire

    private lateinit var textures:Array<MyTexture>

    constructor(_context: Context) {
        context = _context
        shaders_mas=MyShadersCodes()

        modelMatrix= FloatArray(16)
        viewMatrix= FloatArray(16)
        modelViewMatrix= FloatArray(16)
        projectionMatrix= FloatArray(16)
        modelViewProjectionMatrix=FloatArray(16)

        x_light=0.079f //0.079f
        y_light=0.291f//0.291f//0.341f//0.491
        z_light=0.839f//0.879f//1.279
        Matrix.setIdentityM(modelMatrix,0)
        x_camera=0f
        y_camera=1f
        z_camera=3f
        Matrix.setLookAtM(viewMatrix,0,x_camera,y_camera,z_camera,0f,0f,0f,0f,1f,0f)
    }

    override fun onSurfaceCreated(p0: GL10?, p1: EGLConfig?) {
        GLES20.glEnable(GL_DEPTH_TEST)
        GLES20.glEnable(GL_CULL_FACE)
        GLES20.glHint(GLES20.GL_GENERATE_MIPMAP_HINT, GLES20.GL_NICEST)
        GLES20.glBlendFunc(GLES20.GL_SRC_ALPHA,GLES20.GL_ONE_MINUS_SRC_ALPHA)

        my_table= MyTable()
        sphere= arrayOf(
            /*arbyz*/MyShpere(0.25f,-0.3f,0.27f,0.4f),
            /*apple*/MyShpere(0.12f,-0.41f,0.14f,0.6f),
            /*apelsin*/MyShpere(0.09f,-0.11f,0.14f,0.6f),
            /*pomidor*/MyShpere(0.09f,-0.22f,0.14f,0.7f)
        )
        glass= MyGlass(0.1f,0.3f,0.2f,0.47f,2.0f)
        glass.setColor(0.4f,0.4f,0.4f,0.4f)
        glass_water= MyGlass(0.08f,0.3f, 0.12f, 0.47f,1.05f)
        glass_water.setColor(0.234f,1.2f,0.4f,0.4f)
        candle=MyCandle(0.04f,0.23f,1f)
        fire= MyFire(context,1.0245f,0.15f,1.1f)
        fire.rotateFire(90f,1f,0f,1f)

        textures= arrayOf(
            /*arbyz*/MyTexture(context,R.drawable.arbuz),
            /*apple*/MyTexture(context,R.drawable.apple),
            /*apelsin*/MyTexture(context,R.drawable.apelsin),
            /*pomidor*/MyTexture(context,R.drawable.pomidor),
            /*table*/MyTexture(context,R.drawable.table)
        )
        shader= arrayOf(
            MyShader(shaders_mas.vertex_sphere_shader,shaders_mas.fragment_tex_shader_light), //0
            MyShader(shaders_mas.vertex_sphere_shader,shaders_mas.fragment_tex_shader_light), //1
            MyShader(shaders_mas.vertex_shader,shaders_mas.fragment_shader_light), //2
            MyShader(shaders_mas.vertex_shader_cup,shaders_mas.fragment_custom_color) //3
        )
    }

    override fun onSurfaceChanged(p0: GL10?, _width: Int, _height: Int) {
        GLES20.glViewport(0, 0, _width, _height)
        GLES20.glClearColor(1f,1f,1f,1f)

        val ratio=(_width.toFloat()/_height.toFloat()).toFloat()
        val k=0.055f
        val left=((-k)*ratio)
        val right=(k*ratio)
        val bottom=-k
        val top=k
        val near=0.1f
        val far=10.0f

        Matrix.frustumM(projectionMatrix,0,left,right,bottom, top, near, far)
    }

    override fun onDrawFrame(p0: GL10?) {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT or GLES20.GL_DEPTH_BUFFER_BIT)

        /* table */
        Matrix.setIdentityM(modelViewProjectionMatrix,0)
        Matrix.multiplyMM(modelViewMatrix,0,viewMatrix,0,modelMatrix,0)
        Matrix.multiplyMM(modelViewProjectionMatrix,0,projectionMatrix,0,modelViewMatrix,0)
        shader[0].useProgram()
        shader[0].linkVertexBuffer(my_table.vertex_buffer)
        shader[0].linkNormalBuffer(my_table.normal_buffer)
        shader[0].linkModelViewProjectionMatrix(modelViewProjectionMatrix)
        shader[0].linkCamera(x_camera, y_camera, z_camera)
        shader[0].linkLightSource(x_light, y_light, z_light)
        shader[0].linkTexture(textures[4].texture_handle)
        var j=0
        while(j<my_table.count_points){
            GLES20.glDrawArrays(GLES20.GL_TRIANGLE_FAN,j,4)
            j+=4
        }


        /* sphere */
        for(i in 0..<sphere.size) {
            Matrix.setIdentityM(modelViewProjectionMatrix, 0)
            Matrix.multiplyMM(modelViewMatrix, 0, viewMatrix, 0, sphere[i].model_matrix, 0)
            Matrix.multiplyMM(modelViewProjectionMatrix, 0, projectionMatrix, 0, modelViewMatrix, 0)
            shader[1].useProgram()
            shader[1].linkVertexBuffer(sphere[i].vertexBuffer)
            shader[1].linkNormalBuffer(sphere[i].normalBuffer)
            shader[1].linkModelViewProjectionMatrix(modelViewProjectionMatrix)
            shader[1].linkCamera(x_camera, y_camera, z_camera)
            shader[1].linkLightSource(x_light, y_light, z_light)
            if(i<textures.size) shader[1].linkTexture(textures[i].texture_handle)
            j = 0
            while (j < sphere[i].n) {
                GLES20.glDrawArrays(GLES20.GL_TRIANGLE_FAN, j, 4)
                j += 4
            }
        }

        /* glass */
        Matrix.setIdentityM(modelViewProjectionMatrix,0)
        Matrix.multiplyMM(modelViewMatrix,0,viewMatrix,0,glass.model_matrix,0)
        Matrix.multiplyMM(modelViewProjectionMatrix,0,projectionMatrix,0,modelViewMatrix,0)
        shader[3].useProgram()
        shader[3].linkVertexBuffer(glass.vertex_buffer)
        shader[3].linkNormalBuffer(glass.normal_buffer)
        shader[3].linkModelViewProjectionMatrix(modelViewProjectionMatrix)
        shader[3].linkCamera(x_camera, y_camera, z_camera)
        shader[3].linkLightSource(x_light, y_light, z_light)
        shader[3].linkCustomColor(glass.r_color,glass.g_color,glass.b_color,glass.a_color)
        GLES20.glEnable(GL_BLEND)
        j = 0
        while (j < glass.n) {
            GLES20.glDrawArrays(GLES20.GL_TRIANGLE_FAN, j, 4)
            j += 4
        }
        GLES20.glDisable(GL_BLEND)

        /* glass water */
        Matrix.setIdentityM(modelViewProjectionMatrix,0)
        Matrix.multiplyMM(modelViewMatrix,0,viewMatrix,0,glass_water.model_matrix,0)
        Matrix.multiplyMM(modelViewProjectionMatrix,0,projectionMatrix,0,modelViewMatrix,0)
        shader[3].useProgram()
        shader[3].linkVertexBuffer(glass_water.vertex_buffer)
        shader[3].linkNormalBuffer(glass_water.normal_buffer)
        shader[3].linkModelViewProjectionMatrix(modelViewProjectionMatrix)
        shader[3].linkCamera(x_camera, y_camera, z_camera)
        shader[3].linkLightSource(x_light, y_light, z_light)
        shader[3].linkCustomColor(glass_water.r_color,glass_water.g_color,glass_water.b_color,glass_water.a_color)
        GLES20.glEnable(GL_BLEND)
        j = 0
        while (j < glass_water.n) {
            GLES20.glDrawArrays(GLES20.GL_TRIANGLE_FAN, j, 4)
            j += 4
        }
        GLES20.glDisable(GL_BLEND)

        /* candle */
        Matrix.setIdentityM(modelViewProjectionMatrix,0)
        Matrix.multiplyMM(modelViewMatrix,0,viewMatrix,0,candle.model_matrix,0)
        Matrix.multiplyMM(modelViewProjectionMatrix,0,projectionMatrix,0,modelViewMatrix,0)
        shader[2].useProgram()
        shader[2].linkVertexBuffer(candle.vertex_buffer)
        shader[2].linkNormalBuffer(candle.normal_buffer)
        shader[2].linkModelViewProjectionMatrix(modelViewProjectionMatrix)
        shader[2].linkCamera(x_camera, y_camera, z_camera)
        shader[2].linkLightSource(x_light, y_light, z_light)
        j=0
        while(j<candle.count_points) {
            GLES20.glDrawArrays(GLES20.GL_TRIANGLE_FAN, j, 4)
            j += 4
        }

        /* fire */
        Matrix.setIdentityM(modelViewProjectionMatrix,0)
        Matrix.multiplyMM(modelViewMatrix,0,viewMatrix,0,fire.model_matrix,0)
        Matrix.multiplyMM(modelViewProjectionMatrix,0,projectionMatrix,0,modelViewMatrix,0)
        shader[3].useProgram()
        shader[3].linkVertexBuffer(fire.vertexBuffer)
        shader[3].linkNormalBuffer(fire.normalBuffer)
        shader[3].linkModelViewProjectionMatrix(modelViewProjectionMatrix)
        shader[3].linkCamera(x_camera, y_camera, z_camera)
        shader[3].linkLightSource(x_light, y_light, z_light)
        shader[3].linkCustomColor(1f,0f,0f,1f)
        GLES20.glEnable(GL_BLEND)
        fire.getVertex()
        fire.getNormal()
        GLES20.glDrawElements(GLES20.GL_TRIANGLE_STRIP,fire.sizeindex,GLES20.GL_UNSIGNED_SHORT,fire.indexBuffer)
        GLES20.glDisable(GL_BLEND)
    }
}