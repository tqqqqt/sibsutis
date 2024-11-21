package com.example.astronomicalhandbook

import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import javax.microedition.khronos.opengles.GL10

class MyButtons {
    private var vertex_buffer: FloatBuffer
    private var vertices: FloatArray

    constructor(type_button: Int){
        vertices= arrayOf(1f).toFloatArray()
        if(type_button==1){
            vertices = arrayOf(/*main side*/
                0f, 2f, 0f,
                -3f, 2f, 0f,
                -3f, 3f, 0f,
                -4f, 1f, 0f,
                -3f, -1f, 0f,
                -3f, 0f, 0f,
                0f, 0f, 0f
            ).toFloatArray()
        }
        else if(type_button==2){
            vertices = arrayOf(/*main side*/
                0f, 2f, 0f,
                3f, 2f, 0f,
                3f, 3f, 0f,
                4f, 1f, 0f,
                3f, -1f, 0f,
                3f, 0f, 0f,
                0f, 0f, 0f
            ).toFloatArray()
        }
        else if(type_button==3){
            vertices = arrayOf(/*main side*/
                2f, 2f, 0f,
                2f, -2f, 0f,
                -2f, -2f, 0f,
                -2f, 2f, 0f
            ).toFloatArray()
        }
        val byte_buf: ByteBuffer = ByteBuffer.allocateDirect(vertices.size*4)
        byte_buf.order(ByteOrder.nativeOrder())
        vertex_buffer=byte_buf.asFloatBuffer()
        vertex_buffer.put(vertices)
        vertex_buffer.position(0)
    }

    fun draw(gl: GL10){
        gl.glEnableClientState(GL10.GL_VERTEX_ARRAY)
        gl.glVertexPointer(3, GL10.GL_FLOAT,0,vertex_buffer)
        gl.glEnable(GL10.GL_BLEND)
        gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA)
        gl.glColor4f(1f,1f,1f,1f)
        gl.glDrawArrays(GL10.GL_LINE_LOOP,0,vertices.size/3)
        gl.glDisableClientState(GL10.GL_VERTEX_ARRAY)
        gl.glDisable(GL10.GL_BLEND)
    }
}