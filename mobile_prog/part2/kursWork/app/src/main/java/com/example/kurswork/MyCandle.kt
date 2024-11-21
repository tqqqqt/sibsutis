package com.example.kurswork

import android.opengl.Matrix
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer

class MyCandle {
    var model_matrix:FloatArray

    private var vertex_data:FloatArray
    var vertex_buffer: FloatBuffer

    private var normal_data:FloatArray
    var normal_buffer: FloatBuffer

    var count_points=0

    constructor(x_coord:Float, y_coord:Float, z_coord:Float){
        model_matrix= FloatArray(16)
        Matrix.setIdentityM(model_matrix,0)
        Matrix.translateM(model_matrix,0,x_coord,y_coord,z_coord)
        Matrix.scaleM(model_matrix,0,0.5f,1f,1f)

        vertex_data = createVertexData()
        count_points=vertex_data.size/3
        vertex_buffer = ByteBuffer.allocateDirect(vertex_data.size * 4).order(ByteOrder.nativeOrder()).asFloatBuffer()
        vertex_buffer.put(vertex_data)
        vertex_buffer.position(0)

        normal_data = createNormalData()
        normal_buffer = ByteBuffer.allocateDirect(normal_data.size * 4).order(ByteOrder.nativeOrder()).asFloatBuffer()
        normal_buffer.put(normal_data)
        normal_buffer.position(0)
    }

    private fun createVertexData():FloatArray{
        var temp_vertex= arrayOf(
            /*front side*/
            -0.05f, 0f, 0.27f,
            0.02f, 0f, 0.3f,
            0.02f, 0.2f, 0.3f,
            -0.05f, 0.2f, 0.27f,
            /*right front side*/
            0.02f, 0f, 0.3f,
            0.06f, 0.01f, 0.27f,
            0.06f, 0.21f, 0.27f,
            0.02f, 0.2f, 0.3f,
            /*up side*/
            -0.05f, 0.2f, 0.27f,
            0.02f, 0.2f, 0.3f,
            0.06f, 0.21f, 0.27f,
            0.005f, 0.197f, 0.21f
        )
        return temp_vertex.toFloatArray()
    }

    private fun createNormalData():FloatArray{
        var temp_normal= arrayOf(
            /*front side*/
            0f, 0f, 0.014f,
            0f, 0f, 0.014f,
            0f, 0f, 0.014f,
            0f, 0f, 0.014f,
            /*right front side*/
            0.003f, -0.0012f, 0.0126f,
            0.003f, -0.0012f, 0.0126f,
            0.003f, -0.0012f, 0.0126f,
            0.003f, -0.0012f, 0.0126f,
            /*up side*/
            0f, 1f, 1f,
            0f, 1f, 1f,
            0f, 1f, 1f,
            0f, 1f, 1f
        )
        return temp_normal.toFloatArray()
    }
}