package com.example.astronomicalhandbook

import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import javax.microedition.khronos.opengles.GL10

class Sphere {
    public var vertexBuffer: FloatBuffer
    public var textureBuffer: FloatBuffer
    private var vertexData: FloatArray
    private var textureData: FloatArray
    private var n=0

    private var radius:Float

    constructor(_radius:Float){
        radius=_radius
        vertexData = createVertexData()
        textureData = createTextureData()

        vertexBuffer = ByteBuffer.allocateDirect(vertexData.size * 3 * 4).order(ByteOrder.nativeOrder()).asFloatBuffer()
        vertexBuffer.put(vertexData)
        vertexBuffer.position(0)

        textureBuffer = ByteBuffer.allocateDirect(textureData.size * 2 * 4).order(ByteOrder.nativeOrder()).asFloatBuffer()
        textureBuffer.put(textureData)
        textureBuffer.position(0)
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

    fun getRadius() : Float{
        return radius
    }

    private fun createTextureData(): FloatArray {
        val textureList = mutableListOf<Float>()
        val dtheta=15
        val dphi=15
        var theta=-90
        while(theta<=(90-dtheta)) {
            var phi = 0
            while (phi <= (360 - dphi)) {
                textureList.add(phi/360f)
                textureList.add((90+theta)/180f)

                textureList.add(phi/360f)
                textureList.add((90+theta+dtheta)/180f)

                textureList.add((phi+dphi)/360f)
                textureList.add((90+theta+dtheta)/180f)

                textureList.add((phi+dphi)/360f)
                textureList.add((90+theta)/180f)
                phi+=dphi
            }
            theta+=dtheta
        }
        return textureList.toFloatArray()
    }

    fun draw(gl: GL10){
        gl.glFrontFace(GL10.GL_CCW)
        gl.glEnable(GL10.GL_CULL_FACE)
        gl.glCullFace(GL10.GL_BACK)

        gl.glEnableClientState(GL10.GL_VERTEX_ARRAY)
        gl.glVertexPointer(3,GL10.GL_FLOAT,0,vertexBuffer)
        var i=0
        while(i<n){
            gl.glDrawArrays(GL10.GL_TRIANGLE_FAN,i,4)
            i+=4
        }
        gl.glDisableClientState(GL10.GL_VERTEX_ARRAY)
        gl.glDisable(GL10.GL_CULL_FACE)
    }
}