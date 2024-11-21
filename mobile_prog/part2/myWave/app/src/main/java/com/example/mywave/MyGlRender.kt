package com.example.mywave

import android.annotation.SuppressLint
import android.content.Context
import android.opengl.GLES20
import android.opengl.GLSurfaceView
import android.opengl.Matrix
import android.util.Log
import java.nio.FloatBuffer
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGlRender: GLSurfaceView.Renderer {
    private var context:Context
    private lateinit var shader:MyShader

    private var x_camera:Float
    private var y_camera:Float
    private var z_camera:Float
    private var xLightPosition:Float
    private var yLightPosition:Float
    private var zLightPosition:Float

    private var modelMatrix:FloatArray
    private var viewMatrix:FloatArray
    private var modelViewMatrix:FloatArray
    private var projectionMatrix:FloatArray
    private var modelViewProjectionMatrix:FloatArray

    private lateinit var water_ground:WaterGround

    constructor(_context: Context){
        context=_context
        xLightPosition=5f
        yLightPosition=30f
        zLightPosition=5f
        modelMatrix= FloatArray(16)
        viewMatrix= FloatArray(16)
        modelViewMatrix= FloatArray(16)
        projectionMatrix= FloatArray(16)
        modelViewProjectionMatrix=FloatArray(16)

        Matrix.setIdentityM(modelMatrix,0)
        x_camera=0.3f
        y_camera=1.7f
        z_camera=1.5f
        Matrix.setLookAtM(viewMatrix,0,x_camera,y_camera,z_camera,0f,0f,0f,0f,1f,0f)
        Matrix.multiplyMM(modelViewMatrix,0,viewMatrix,0,modelMatrix,0)
    }

    override fun onSurfaceCreated(p0: GL10?, p1: EGLConfig?) {
        GLES20.glEnable(GLES20.GL_DEPTH_TEST)
        GLES20.glEnable(GLES20.GL_CULL_FACE)
        GLES20.glHint(GLES20.GL_GENERATE_MIPMAP_HINT,GLES20.GL_NICEST)

        water_ground=WaterGround(context)
        shader= MyShader(vertexShaderCode,fragmentShaderCode)
        shader.linkVertexBuffer(water_ground.vertexBuffer)
        shader.linkNormalBuffer(water_ground.normalBuffer)
    }

    override fun onSurfaceChanged(p0: GL10?, _width: Int, _height: Int) {
        GLES20.glViewport(0,0,_width,_height)
        var ratio=(_width.toFloat()/_height.toFloat()).toFloat()
        var k=0.055f
        var left=((-k)*ratio)
        var right=(k*ratio)
        var bottom=-k
        var top=k
        var near=0.1f
        var far=10.0f

        Matrix.frustumM(projectionMatrix,0,left,right,bottom, top, near, far)
        Matrix.multiplyMM(modelViewProjectionMatrix,0,projectionMatrix,0,modelViewMatrix,0)
    }

    override fun onDrawFrame(p0: GL10?) {
        shader.linkModelViewProjectionMatrix(modelViewProjectionMatrix)
        shader.linkCamera(x_camera,y_camera,z_camera)
        shader.linkLightSource(xLightPosition,yLightPosition,zLightPosition)

        water_ground.getVertex()
        water_ground.getNormal()

        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT or GLES20.GL_DEPTH_BUFFER_BIT)
        GLES20.glDrawElements(GLES20.GL_TRIANGLE_STRIP,water_ground.sizeindex,GLES20.GL_UNSIGNED_SHORT,water_ground.indexBuffer)
    }



    private var vertexShaderCode=
    "uniform mat4 u_modelViewProjectionMatrix;"+
    "attribute vec3 a_vertex;"+
    "attribute vec3 a_normal;"+
    "varying vec3 v_vertex;"+
    "varying vec3 v_normal;"+
    "void main() {"+
    "v_vertex=a_vertex;"+
    "vec3 n_normal=normalize(a_normal);"+
    "v_normal=n_normal;"+
    "gl_Position = u_modelViewProjectionMatrix * vec4(a_vertex,1.0);"+
    "}"

    private var fragmentShaderCode=
    "precision mediump float;"+
    "uniform vec3 u_camera;"+
    "uniform vec3 u_lightPosition;"+
    "varying vec3 v_vertex;"+
    "varying vec3 v_normal;"+
    "void main() {"+
    "vec3 n_normal=normalize(v_normal);"+
    "vec3 lightvector = normalize(u_lightPosition - v_vertex);"+
    "vec3 lookvector = normalize(u_camera - v_vertex);"+
    "float ambient=0.1;"+
    "float k_diffuse=0.7;"+
    "float k_specular=0.3;"+
    "float diffuse = k_diffuse * max(dot(n_normal, lightvector), 0.0);"+
    "vec3 reflectvector = reflect(-lightvector, n_normal);"+
    "float specular=k_specular*pow( max(dot(lookvector,reflectvector),0.0),40.0);"+
    "vec4 one=vec4(1.0,1.0,1.0,1.0);"+
    "vec4 lightColor=(ambient+diffuse+specular)*one;"+
    "gl_FragColor=lightColor;"+
    "}"
}