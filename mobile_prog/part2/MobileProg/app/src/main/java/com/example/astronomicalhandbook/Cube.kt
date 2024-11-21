package com.example.astronomicalhandbook

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.opengl.GLUtils
import java.io.InputStream
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import javax.microedition.khronos.opengles.GL10

class Cube {
    private var vertex_buffer: FloatBuffer
    var texture_buffer: FloatBuffer
    private var vertices: FloatArray
    private var texture_cord: FloatArray
    private var texture_name: IntArray
    private var textures: IntArray
    private var context: Context
    private var count_draw:Int

    constructor(_context: Context, mode: Int){
        vertices=arrayOf(-20f, -20f, 0.0f,
                        20f, -20f, 0.0f,
                        20f, 20f, 0f,
                        -20f, 20f, 0.0f).toFloatArray()
        texture_cord=arrayOf(1f).toFloatArray()
        if(mode==1) texture_cord=arrayOf(1f, 1f,
                            0f, 1f,
                            0f, 0f,
                            1f, 0f).toFloatArray()
        else if(mode==2) texture_cord= arrayOf(0f,1f,
                            1f,1f,
                            1f,0f,
                            0f,0f).toFloatArray()
        val byte_buf: ByteBuffer = ByteBuffer.allocateDirect(vertices.size*4)
        byte_buf.order(ByteOrder.nativeOrder())
        vertex_buffer=byte_buf.asFloatBuffer()
        vertex_buffer.put(vertices)
        vertex_buffer.position(0)

        context=_context
        count_draw=0
        texture_name= arrayOf(R.drawable.galac).toIntArray()
        textures= arrayOf(0).toIntArray()
        val texture_byte_buf: ByteBuffer=ByteBuffer.allocateDirect(texture_cord.size*4)
        texture_byte_buf.order(ByteOrder.nativeOrder())
        texture_buffer=texture_byte_buf.asFloatBuffer()
        texture_buffer.put(texture_cord)
        texture_buffer.position(0)
    }

    private fun loadGlTexture(gl: GL10){
        gl.glGenTextures(1,textures,0)

        gl.glBindTexture(GL10.GL_TEXTURE_2D,textures[0])
        gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_MIN_FILTER,GL10.GL_LINEAR.toFloat())
        val str:InputStream=context.getResources().openRawResource(texture_name[0])
        val bitmap:Bitmap=BitmapFactory.decodeStream(str)
        GLUtils.texImage2D(GL10.GL_TEXTURE_2D,0,bitmap,0)
        bitmap.recycle()
    }

    fun draw(gl: GL10, mode:Int){
        if(count_draw==0){
            loadGlTexture(gl)
            count_draw++;
        }
        gl.glEnableClientState(GL10.GL_VERTEX_ARRAY)
        gl.glVertexPointer(3,GL10.GL_FLOAT,0,vertex_buffer)
        //gl.glEnable(GL10.GL_BLEND)
        //gl.glBlendFunc(GL10.GL_SRC_ALPHA,GL10.GL_ONE_MINUS_SRC_ALPHA)
        if(mode==0) {
            gl.glEnable(GL10.GL_TEXTURE_2D)
            gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY)
            gl.glBindTexture(GL10.GL_TEXTURE_2D, textures[0])
            gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, texture_buffer)
        }
        gl.glDrawArrays(GL10.GL_TRIANGLE_FAN,0,vertices.size/3)
        gl.glClear(GL10.GL_TEXTURE_2D)
        if(mode==0) {
            gl.glDisable(GL10.GL_TEXTURE_2D)
            gl.glDisableClientState(GL10.GL_TEXTURE_COORD_ARRAY)
        }
        gl.glDisableClientState(GL10.GL_VERTEX_ARRAY)
        //gl.glDisable(GL10.GL_BLEND)
    }
}