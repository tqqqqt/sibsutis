package com.example.kurswork

import android.opengl.Matrix
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer

class MyGlass {
    var model_matrix:FloatArray

    private var vertex_data:FloatArray
    var vertex_buffer:FloatBuffer
    var n=0

    private var normal_data:FloatArray
    var normal_buffer:FloatBuffer

    var count_points=0
    private var radius=0.0f

    var r_color=0f
    var g_color=0f
    var b_color=0f
    var a_color=0f

    constructor(_radius:Float, x_coord:Float, y_coord:Float, z_coord:Float, y_scale:Float){
        model_matrix= FloatArray(16)
        Matrix.setIdentityM(model_matrix,0)
        Matrix.translateM(model_matrix,0,x_coord,y_coord,z_coord)
        Matrix.scaleM(model_matrix,0,1f,y_scale,1f)

        radius=_radius

        vertex_data = createVertexData()
        count_points=vertex_data.size/3
        vertex_buffer = ByteBuffer.allocateDirect(vertex_data.size * 3 * 4).order(ByteOrder.nativeOrder()).asFloatBuffer()
        vertex_buffer.put(vertex_data)
        vertex_buffer.position(0)

        normal_data = createNormalData()
        normal_buffer = ByteBuffer.allocateDirect(normal_data.size * 4).order(ByteOrder.nativeOrder()).asFloatBuffer()
        normal_buffer.put(normal_data)
        normal_buffer.position(0)
    }

    private fun createVertexData():FloatArray{
        val vertexList = mutableListOf<Float>()
        val dtor=(Math.PI/180f).toDouble()
        val dtheta=15
        val dphi=15
        var theta=-90
        while(theta<=(90-dtheta)){
            var phi=180
            while(phi<=(360-dphi)){
                vertexList.add(((Math.cos(theta*dtor)*Math.cos(phi*dtor))*radius).toFloat())
                vertexList.add(((Math.cos(theta*dtor)*Math.sin(phi*dtor))*radius).toFloat())
                vertexList.add(((Math.sin(theta*dtor))*radius).toFloat())

                vertexList.add(((Math.cos((theta+dtheta)*dtor)*Math.cos(phi*dtor))*radius).toFloat())
                vertexList.add(((Math.cos((theta+dtheta)*dtor)*Math.sin(phi*dtor))*radius).toFloat())
                vertexList.add(((Math.sin((theta+dtheta)*dtor))*radius).toFloat())

                vertexList.add(((Math.cos((theta+dtheta)*dtor)*Math.cos((phi+dphi)*dtor))*radius).toFloat())
                vertexList.add(((Math.cos((theta+dtheta)*dtor)*Math.sin((phi+dphi)*dtor))*radius).toFloat())
                vertexList.add(((Math.sin((theta+dtheta)*dtor))*radius).toFloat())

                vertexList.add(((Math.cos(theta*dtor)*Math.cos((phi+dphi)*dtor))*radius).toFloat())
                vertexList.add(((Math.cos(theta*dtor)*Math.sin((phi+dphi)*dtor))*radius).toFloat())
                vertexList.add(((Math.sin(theta*dtor))*radius).toFloat())
                phi+=dphi
                n+=4
            }
            theta+=dtheta
        }
        return vertexList.toFloatArray()
    }

    private fun createNormalData():FloatArray{
        var temp_normal= mutableListOf<Float>()
        var i=0
        while(i<count_points){
            temp_normal.add(1f)
            temp_normal.add(1f)
            temp_normal.add(1f)
            i+=3
        }
        return temp_normal.toFloatArray()
    }

    fun setColor(_r_color:Float, _g_color:Float, _b_color:Float, _a_color:Float){
        r_color=_r_color
        g_color=_g_color
        b_color=_b_color
        a_color=_a_color
    }
}