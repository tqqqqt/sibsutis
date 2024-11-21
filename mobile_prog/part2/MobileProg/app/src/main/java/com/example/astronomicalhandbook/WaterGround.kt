package com.example.astronomicalhandbook

import android.content.Context
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import javax.microedition.khronos.opengles.GL10
import kotlin.math.cos
import kotlin.math.floor

class WaterGround {
    private var vertex_left: FloatArray
    private var vertex_right:FloatArray
    private lateinit var vertex_left_buffer: FloatBuffer
    private lateinit var vertex_right_buffer: FloatBuffer
    private var width_ground:Int
    private var height_ground:Int
    private var curent_diag:Int
    private var diag_array:Array<IntArray>
    private var diag_count:Int
    private var diag_right_count:Int
    private var diag_left_count:Int


    constructor(_context: Context, _widht:Int, _height:Int){
        var temp_vertex= mutableListOf<Float>()
        var temp_diag_vertex= mutableListOf<Int>()
        width_ground=_widht
        height_ground=_height
        diag_array=Array((width_ground*height_ground),{IntArray(0)})
        //global coords
        var y_top=(0+floor((height_ground/2.0))).toFloat()
        var x_top=(0-floor((width_ground/2.0))).toFloat()
        var y_bot=0f
        var x_bot=0f
        if(height_ground%2==0) y_bot = (0 - floor((height_ground / 2.0))+1).toFloat()
        else y_bot= (0 - floor((height_ground / 2.0))).toFloat()
        if(width_ground%2==0) x_bot = (0 + floor((width_ground / 2.0))-1).toFloat()
        else x_bot= (0 + floor((width_ground / 2.0))).toFloat()
        //left triangle
        var i=y_top
        var curent_diag_create=0
        while(i>=y_bot){
            temp_diag_vertex.clear()
            var temp_y=i
            var temp_x=x_top
            while(temp_x<=x_bot && temp_y<=y_top){
                temp_diag_vertex.add(temp_vertex.size)
                temp_vertex.add(temp_x.toFloat())
                temp_vertex.add(temp_y.toFloat())
                temp_vertex.add(0f)
                temp_x+=0.2f
                temp_y+=0.2f
            }
            diag_array[curent_diag_create]=temp_diag_vertex.toIntArray()
            curent_diag_create++
            i-=0.2f
        }
        diag_left_count=curent_diag_create-1
        vertex_left=temp_vertex.toFloatArray()
        loadByteBuffer(1)
        //right triangle
        temp_vertex.clear()
        i=x_bot
        var temp_right=Array((width_ground*height_ground),{IntArray(0)})
        var ttemp=0
        while(i>=x_top){
            temp_diag_vertex.clear()
            var temp_y=y_bot
            var temp_x=i
            while(temp_x<=x_bot && temp_y<=y_top){
                temp_diag_vertex.add(temp_vertex.size)
                temp_vertex.add(temp_x.toFloat())
                temp_vertex.add(temp_y.toFloat())
                temp_vertex.add(0f)
                temp_x+=0.2f
                temp_y+=0.2f
            }
            temp_right[ttemp]=temp_diag_vertex.toIntArray()
            ttemp++
            i-=0.2f
        }
        vertex_right=temp_vertex.toFloatArray()
        //merge diaganals vertex index
        for(ii in ttemp-1 downTo 0){
            diag_array[curent_diag_create++]=temp_right[ii]
        }
        loadByteBuffer(2)
        //global params
        diag_count=curent_diag_create-1
        diag_right_count=curent_diag_create-diag_left_count-1
        curent_diag=1
    }

    private fun loadByteBuffer(mode:Int){
        if(mode==1) {
            val byte_buf: ByteBuffer = ByteBuffer.allocateDirect(vertex_left.size * 4)
            byte_buf.order(ByteOrder.nativeOrder())
            vertex_left_buffer = byte_buf.asFloatBuffer()
            vertex_left_buffer.put(vertex_left)
            vertex_left_buffer.position(0)
        }
        else{
            val byte_buf: ByteBuffer = ByteBuffer.allocateDirect(vertex_right.size * 4)
            byte_buf.order(ByteOrder.nativeOrder())
            vertex_right_buffer = byte_buf.asFloatBuffer()
            vertex_right_buffer.put(vertex_right)
            vertex_right_buffer.position(0)
        }
    }

    private fun wave(){
        // 0 point -> [0]x [1]y(need + or -) [2]z
        // 1 point -> [3]x [4]y [5]z
        if(curent_diag>diag_count) curent_diag=0
        else curent_diag++

        var time=System.currentTimeMillis()
        for(i in 0..<diag_array[curent_diag].size){
            /*if(curent_diag<=diag_left_count) vertex_left[diag_array[curent_diag][i]+2]-=0.2f
            else vertex_right[diag_array[curent_diag][i]+2]-=0.2f*/
            if(curent_diag<=diag_left_count) vertex_left[diag_array[curent_diag][i]+2]=0.2f* cos(0.005f*time+5*(vertex_left[diag_array[curent_diag][i]+1]+vertex_left[diag_array[curent_diag][i]]))//=0.2f
            else vertex_right[diag_array[curent_diag][i]+2]-=0.2f
        }
        /*var temp=curent_diag-1
        if(temp>=0){
            for(j in 0..<diag_array[temp].size){
                if(temp<=diag_left_count) vertex_left[diag_array[temp][j]+2]+=0.2f
                else vertex_right[diag_array[temp][j]+2]+=0.2f
            }
        }*/

        if(curent_diag<=diag_left_count) loadByteBuffer(1)
        else loadByteBuffer(2)
        /*if(temp<=diag_left_count) loadByteBuffer(1)
        else loadByteBuffer(2)*/
    }

    fun draw(gl: GL10){
        wave()
        gl.glEnableClientState(GL10.GL_VERTEX_ARRAY)
        gl.glEnable(GL10.GL_DEPTH_TEST)
        gl.glPushMatrix()
        gl.glRotatef(60f,1f,0f,0f)
        gl.glRotatef(-15f,0f,1f,0f)
        gl.glVertexPointer(3, GL10.GL_FLOAT,0,vertex_left_buffer)
        gl.glDrawArrays(GL10.GL_TRIANGLE_FAN,0,vertex_left.size/3)
        gl.glVertexPointer(3, GL10.GL_FLOAT,0,vertex_right_buffer)
        gl.glDrawArrays(GL10.GL_TRIANGLE_FAN,0,vertex_right.size/3)
        gl.glPopMatrix()
        gl.glDisable(GL10.GL_DEPTH_TEST)
        gl.glDisableClientState(GL10.GL_VERTEX_ARRAY)
    }
}