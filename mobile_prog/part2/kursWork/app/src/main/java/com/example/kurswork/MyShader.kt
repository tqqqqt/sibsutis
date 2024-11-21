package com.example.kurswork

import android.opengl.GLES20
import java.nio.FloatBuffer

class MyShader {
    private var program_handle=0

    constructor(_vertex_shader:String, _fragment_shader:String){
        createProgram(_vertex_shader,_fragment_shader)
    }

    private fun createProgram(vertex_shader:String, fragment_shader:String){
        val vertex_shader_handle= GLES20.glCreateShader(GLES20.GL_VERTEX_SHADER)
        GLES20.glShaderSource(vertex_shader_handle,vertex_shader)
        GLES20.glCompileShader(vertex_shader_handle)
        val fragment_shader_handle=GLES20.glCreateShader(GLES20.GL_FRAGMENT_SHADER)
        GLES20.glShaderSource(fragment_shader_handle,fragment_shader)
        GLES20.glCompileShader(fragment_shader_handle)
        program_handle=GLES20.glCreateProgram()
        GLES20.glAttachShader(program_handle,vertex_shader_handle)
        GLES20.glAttachShader(program_handle,fragment_shader_handle)
        GLES20.glLinkProgram(program_handle)
    }

    fun linkVertexBuffer(vertex_buffer: FloatBuffer){
        GLES20.glUseProgram(program_handle)
        val a_vertex_handle=GLES20.glGetAttribLocation(program_handle,"a_vertex");
        GLES20.glEnableVertexAttribArray(a_vertex_handle)
        GLES20.glVertexAttribPointer(a_vertex_handle,3,GLES20.GL_FLOAT,false,0,vertex_buffer)
    }

    fun linkNormalBuffer(normal_buffer:FloatBuffer){
        GLES20.glUseProgram(program_handle)
        val a_vertex_handle=GLES20.glGetAttribLocation(program_handle,"a_normal");
        GLES20.glEnableVertexAttribArray(a_vertex_handle)
        GLES20.glVertexAttribPointer(a_vertex_handle,3,GLES20.GL_FLOAT,false,0,normal_buffer)
    }

    fun linkModelViewProjectionMatrix(model_view_projection_matrix:FloatArray){
        GLES20.glUseProgram(program_handle)
        val u_model_handle=GLES20.glGetUniformLocation(program_handle,"u_modelViewProjectionMatrix")
        GLES20.glUniformMatrix4fv(u_model_handle,1,false,model_view_projection_matrix,0)
    }

    fun linkCamera(x_camera:Float, y_camera:Float, z_camera:Float){
        GLES20.glUseProgram(program_handle)
        val u_camera_handle=GLES20.glGetUniformLocation(program_handle,"u_camera")
        GLES20.glUniform3f(u_camera_handle,x_camera,y_camera,z_camera)
    }

    fun linkLightSource(x_light:Float, y_light:Float, z_light:Float){
        GLES20.glUseProgram(program_handle)
        val u_light_handle=GLES20.glGetUniformLocation(program_handle,"u_lightPosition")
        GLES20.glUniform3f(u_light_handle,x_light,y_light,z_light)
    }

    fun linkTexture(texture_name:Int){
        GLES20.glUseProgram(program_handle)
        val u_texture_handle=GLES20.glGetUniformLocation(program_handle,"u_texture")
        GLES20.glActiveTexture(GLES20.GL_TEXTURE0)
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D,texture_name)
        GLES20.glUniform1i(u_texture_handle,0)
    }

    fun linkCustomColor(r_color:Float, g_color:Float, b_color:Float, a_color:Float){
        GLES20.glUseProgram(program_handle)
        val u_custom_color=GLES20.glGetUniformLocation(program_handle,"u_color")
        GLES20.glUniform4f(u_custom_color,r_color,g_color,b_color,a_color)
    }

    fun useProgram(){
        GLES20.glUseProgram(program_handle)
    }
}