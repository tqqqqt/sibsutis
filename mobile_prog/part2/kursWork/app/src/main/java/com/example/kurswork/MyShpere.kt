package com.example.kurswork

import android.opengl.Matrix
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import java.util.Vector

class MyShpere {
    var model_matrix: FloatArray

    private var vertexData: FloatArray
    var vertexBuffer: FloatBuffer
    var n=0

    private var normalData: FloatArray
    var normalBuffer:FloatBuffer

    private var radius:Float
    private var global_x:Float
    private var global_y:Float
    private var global_z:Float

    constructor(_radius:Float, _x_coord:Float, _y_coord:Float, _z_coord:Float){
        radius=_radius
        global_x=_x_coord
        global_y=_y_coord
        global_z=_z_coord

        model_matrix= FloatArray(16)
        Matrix.setIdentityM(model_matrix,0)
        Matrix.translateM(model_matrix,0,_x_coord,_y_coord,_z_coord)

        vertexData = createVertexData()
        vertexBuffer = ByteBuffer.allocateDirect(vertexData.size * 3 * 4).order(ByteOrder.nativeOrder()).asFloatBuffer()
        vertexBuffer.put(vertexData)
        vertexBuffer.position(0)

        normalData=createNormalData()
        normalBuffer=ByteBuffer.allocateDirect(normalData.size*4).order(ByteOrder.nativeOrder()).asFloatBuffer()
        normalBuffer.put(normalData)
        normalBuffer.position(0)
    }

    private fun createVertexData(): FloatArray {
        val vertexList = mutableListOf<Float>()
        val dtor=(Math.PI/180f).toDouble()
        val dtheta=15
        val dphi=15
        var theta=-90
        while(theta<=(90-dtheta)){
            var phi=0
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
        while(i<vertexData.size){
            var AB= arrayOf(vertexData[i+3]-vertexData[i],vertexData[i+4]-vertexData[i+1],vertexData[i+5]-vertexData[i+2]).toFloatArray()
            var AC= arrayOf(vertexData[i+6]-vertexData[i],vertexData[i+7]-vertexData[i+1],vertexData[i+8]-vertexData[i+2]).toFloatArray()
            var CD= arrayOf(vertexData[i+9]-vertexData[i+6],vertexData[i+10]-vertexData[i+7],vertexData[i+11]-vertexData[i+8]).toFloatArray()
            var CA= arrayOf(vertexData[i]-vertexData[i+6],vertexData[i+1]-vertexData[i+7],vertexData[i+2]-vertexData[i+8]).toFloatArray()
            var ABxAC= arrayOf((AB[1]*AC[2])-(AB[2]*AC[1]),(AB[2]*AC[0])-(AB[0]*AC[2]),(AB[0]*AC[1])-(AB[1]*AC[0])).toFloatArray()
            var CDxCA= arrayOf((CD[1]*CA[2])-(CD[2]*CA[1]),(CD[2]*CA[0])-(CD[0]*CA[2]),(CD[0]*CA[1])-(CD[1]*CA[0])).toFloatArray()
            for(j in 0..1) {
                temp_normal.add(ABxAC[0])
                temp_normal.add(ABxAC[1])
                temp_normal.add(ABxAC[2])
            }
            for(j in 0..1) {
                temp_normal.add(CDxCA[0])
                temp_normal.add(CDxCA[1])
                temp_normal.add(CDxCA[2])
            }
            i+=12
        }
        return temp_normal.toFloatArray()
    }
}