package com.example.kurswork

import android.content.Context
import android.graphics.BitmapFactory
import android.opengl.GLES20
import android.opengl.GLUtils

class MyTexture {
    private var context:Context
    var texture_handle=0

    constructor(_context:Context, id_picture:Int){
        context=_context
        var names=IntArray(1)
        GLES20.glGenTextures(1,names,0)
        texture_handle=names[0]
        GLES20.glPixelStorei(GLES20.GL_UNPACK_ALIGNMENT,1)
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D,texture_handle)
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D,GLES20.GL_TEXTURE_MIN_FILTER,GLES20.GL_LINEAR_MIPMAP_LINEAR)
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR)
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D,
            GLES20.GL_TEXTURE_WRAP_S,
            GLES20.GL_REPEAT);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D,
            GLES20.GL_TEXTURE_WRAP_T,
            GLES20.GL_REPEAT);
        var bitmap=BitmapFactory.decodeResource(context.resources,id_picture)
        GLUtils.texImage2D(GLES20.GL_TEXTURE_2D,0,bitmap,0)
        bitmap.recycle()
        GLES20.glGenerateMipmap(GLES20.GL_TEXTURE_2D)
    }
}