package com.example.kurswork

import android.opengl.Matrix
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer

class MyTable {
    var count_points=0

    var model_matrix:FloatArray

    var vertex_buffer:FloatBuffer
    var normal_buffer:FloatBuffer

    constructor(){
        model_matrix= FloatArray(16)
        Matrix.setIdentityM(model_matrix,0)

        var temp_vertex=createVertexData()
        var temp_normal=createNormalData()

        count_points=temp_vertex.size/3
        var vb=ByteBuffer.allocateDirect(temp_vertex.size*4)
        vb.order(ByteOrder.nativeOrder())
        vertex_buffer=vb.asFloatBuffer()
        vertex_buffer.put(temp_vertex)
        vertex_buffer.position(0)

        var nb=ByteBuffer.allocateDirect(temp_normal.size*4)
        nb.order(ByteOrder.nativeOrder())
        normal_buffer=nb.asFloatBuffer()
        normal_buffer.put(temp_normal)
        normal_buffer.position(0)
    }

    fun createVertexData():FloatArray{
        var temp_vertex= arrayOf(
            /*up side*/
            -0.8f, 0f, 1.2f,
            0.8f, 0f, 1.2f,
            0.5f, 0f, 0.02f,
            -0.5f, 0f, 0.02f,
            /*front side*/
            -0.8f, -0.1f, 1.1f,
            0.8f, -0.1f, 1.1f,
            0.8f, 0f, 1.2f,
            -0.8f, 0f, 1.2f,
            /*back left leg*/
            -0.5f, -1.0f, 0.01f,
            -0.4f, -1.0f, 0.01f,
            -0.4f, 0f, 0.02f,
            -0.5f, 0f, 0.02f,
            /*back left back side*/
            -0.4f, -1.0f, 0.01f,
            -0.37f, -0.97f, 0.0009f,
            -0.37f, 0f, 0.0009f,
            -0.5f, 0f, 0.02f,
            /*back right leg*/
            0.4f, -1f, 0.01f,
            0.5f, -1f, 0.01f,
            0.5f, 0f, 0.02f,
            0.4f, 0f, 0.02f,
            /*back right back side*/
            0.37f, -0.97f, 0.0009f,
            0.4f, -1f, 0.01f,
            0.4f, 0f, 0.02f,
            0.35f, 0f, 0.02f
        ).toFloatArray()
        return temp_vertex
    }

    fun createNormalData():FloatArray{
        var temp_normal= arrayOf(
            /*up side*/
            0f, 1f, 0f,
            0f, 1f, 0f,
            0f, 1f, 0f,
            0f, 1f, 0f,
            /*front side*/
            0f, -0.16f, 0.16f,
            0f, -0.16f, 0.16f,
            0f, -0.16f, 0.16f,
            0f, -0.16f, 0.16f,
            /*back left leg*/
            0f, -0.0f, 0.1f, //-0.01
            0f, -0.0f, 0.1f,
            0f, -0.0f, 0.1f,
            0f, -0.0f, 0.1f,
            /*back left back side*/
            0f, 0f, 0.0291f,
            0f, 0f, 0.0291f,
            0f, -0.00034f, 0.13f,
            0f, -0.00034f, 0.13f,
            /*back right leg*/
            0f, -0.01f, 0.1f,
            0f, -0.01f, 0.1f,
            0f, -0.01f, 0.1f,
            0f, -0.01f, 0.1f,
            /*back right back side*/
            -0.00901f, 0f, 0.0291f,
            -0.00901f, 0f, 0.0291f,
            0f, -0.000955f, 0.0485f,
            0f, -0.000955f, 0.0485f,
        ).toFloatArray()
        return temp_normal
    }
}