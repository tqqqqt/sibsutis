package com.example.astronomicalhandbook

import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import javax.microedition.khronos.opengles.GL10

class Square {
    private var vertex_buffer: FloatBuffer
    private var vertices: FloatArray

    constructor(){
        vertices=arrayOf(/*main side*/
                        -0.5f, -0.5f, 0.0f,
                        0.5f, -0.5f, 0.0f,
                        0.5f, 0.5f, 0f,
                        -0.5f, 0.5f, 0.0f,
                        /*back side*/
                        0f, 0.75f, -2f,
                        0.75f, 0.75f, -2f,
                        0.75f, -0.25f, -2f,
                        0.5f, -0.5f, -2f,
                        0.5f, 0.5f, -2f,
                        0.75f, 0.75f, -2f).toFloatArray()
        val byte_buf: ByteBuffer = ByteBuffer.allocateDirect(vertices.size*4)
        byte_buf.order(ByteOrder.nativeOrder())
        vertex_buffer=byte_buf.asFloatBuffer()
        vertex_buffer.put(vertices)
        vertex_buffer.position(0)
    }

    fun changeVertex(planet_radius: Float){
        vertices=arrayOf(/*main side*/
            -planet_radius, -planet_radius, 0.0f,
            planet_radius, -planet_radius, 0.0f,
            planet_radius, planet_radius, 0f,
            -planet_radius, planet_radius, 0.0f,
            /*back side*/
            0f, planet_radius+(planet_radius/2), -planet_radius,
            planet_radius+(planet_radius/2), planet_radius+(planet_radius/2), -planet_radius,
            planet_radius+(planet_radius/2), -planet_radius+(planet_radius/2), -planet_radius,
            planet_radius, -planet_radius, -planet_radius,
            planet_radius, planet_radius, -planet_radius,
            planet_radius+(planet_radius/2), planet_radius+(planet_radius/2), -planet_radius).toFloatArray()
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
        gl.glColor4f(1f,1f,1f,0.4f)
        gl.glDrawArrays(GL10.GL_TRIANGLE_FAN,0,vertices.size/3)
        gl.glDisableClientState(GL10.GL_VERTEX_ARRAY)
        gl.glDisable(GL10.GL_BLEND)
    }
}