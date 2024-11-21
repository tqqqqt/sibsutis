package com.example.blackhole

import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer

class MyBlackHole {
    var vertex_buffer:FloatBuffer

    constructor(){
        var temp_vertex= arrayOf(-1f, 1f, 0f,
                                1f, 1f, 0f,
                                1f, -1f, 0f,
                                1f, -1f, 0f,
                                -1f, -1f, 0f,
                                -1f, 1f, 0f).toFloatArray()
        var tv=ByteBuffer.allocateDirect((temp_vertex.size*4))
        tv.order(ByteOrder.nativeOrder())
        vertex_buffer=tv.asFloatBuffer()
        vertex_buffer.put(temp_vertex)
        vertex_buffer.position(0)
    }
}