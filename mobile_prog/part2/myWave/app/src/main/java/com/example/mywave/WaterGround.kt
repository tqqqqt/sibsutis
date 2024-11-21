package com.example.mywave

import android.content.Context
import android.util.Log
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import java.nio.ShortBuffer
import kotlin.math.cos
import kotlin.math.exp
import kotlin.math.floor

class WaterGround {
    private var context:Context

    private var imax=49
    private var jmax=49
    var sizeindex:Int
    private var x0=-1f;
    private var z0=-1f;
    private var dx=0.04f;
    private var dz=0.04f;
    private var x:FloatArray
    private var y:Array<FloatArray>
    private var z:FloatArray
    private var vertex:FloatArray

    private var normalX:Array<FloatArray>
    private var normalY:Array<FloatArray>
    private var normalZ:Array<FloatArray>
    private var normal:FloatArray
    var vertexBuffer:FloatBuffer
    var normalBuffer:FloatBuffer

    var indexBuffer:ShortBuffer


    constructor(_context:Context){
        context=_context

        x=FloatArray(imax+1)
        z=FloatArray(jmax+1)
        y=Array(jmax+1,{ FloatArray(imax+1) })
        vertex=FloatArray((jmax+1)*(imax+1)*3)
        normalX=Array(jmax+1,{ FloatArray(imax+1) })
        normalY=Array(jmax+1,{ FloatArray(imax+1) })
        normalZ=Array(jmax+1,{ FloatArray(imax+1) })
        normal=FloatArray((jmax+1)*(imax+1)*3)

        for(i in 0..imax) x[i]=x0+i*dx
        for(j in 0..jmax) z[j]=z0+j*dz

        var vb=ByteBuffer.allocateDirect((jmax+1)*(imax+1)*3*4)
        vb.order(ByteOrder.nativeOrder())
        vertexBuffer=vb.asFloatBuffer()
        vertexBuffer.position(0)
        var nb=ByteBuffer.allocateDirect((jmax+1)*(imax+1)*3*4)
        nb.order(ByteOrder.nativeOrder())
        normalBuffer=nb.asFloatBuffer()
        normalBuffer.position(0)

        sizeindex=2*(imax+1)*jmax+(jmax-1)
        var index=ShortArray(sizeindex)
        var k=0
        var j=0
        while(j<jmax){
            for(i in 0..imax){
                index[k++]=chain(j,i)
                index[k++]=chain(j+1,i)
            }
            if(j<jmax-1) index[k++]=chain(j+1,imax)
            j++
            if(j<jmax){
                for(i in imax downTo 0){
                    index[k++]=chain(j,i)
                    index[k++]=chain((j+1),i)
                }
                if(j<jmax-1) index[k++]=chain((j+1),0)
                j++
            }
        }

        var bi=ByteBuffer.allocateDirect(sizeindex*2)
        bi.order(ByteOrder.nativeOrder())
        indexBuffer=bi.asShortBuffer()
        indexBuffer.put(index)
        indexBuffer.position(0)

        index=ShortArray(0)

        getVertex()
        getNormal()
    }

    private fun chain(j:Int, i:Int):Short{
        return (i+j*(imax+1)).toShort()
    }

    fun getVertex(){
        var time=System.currentTimeMillis()
        for(j in 0..jmax){
            for(i in 0..imax){
                var temp_cos=(Math.cos(0.005*time+(5f*(z[j]+x[i])))).toFloat()
                y[j][i]=0.04f*temp_cos.toFloat()
            }
        }
        var k=0
        for(j in 0..jmax){
            for(i in 0..imax){
                vertex[k++]=x[i]
                vertex[k++]=y[j][i]
                vertex[k++]=z[j]
            }
        }
        vertexBuffer.put(vertex)
        vertexBuffer.position(0)
    }

    fun getNormal(){
        for (j in 0..<jmax){
            for (i in 0..<imax){
                normalX[j][i]=-(y[j][i+1]-y[j][i])*dz
                normalY[j][i]=dx*dz
                normalZ[j][i]=-dx*(y[j+1][i]-y[j][i])
            }
        }
        for (j in 0..<jmax){
            normalX[j][imax]=(y[j][imax-1]-y[j][imax])*dz
            normalY[j][imax]=dx*dz
            normalZ[j][imax]=-dx*(y[j+1][imax]-y[j][imax])
        }
        for (i in 0..<imax){
            normalX[jmax][i]=-(y[jmax][i+1]-y[jmax][i])*dz
            normalY[jmax][i]=dx*dz
            normalZ[jmax][i]=dx*(y[jmax-1][i]-y[jmax][i])
        }
        normalX[jmax][imax]=(y[jmax][imax-1]-y[jmax][imax])*dz
        normalY[jmax][imax]=dx*dz
        normalZ[jmax][imax]=dx*(y[jmax-1][imax]-y[jmax][imax])
        var k=0
        for (j in 0..jmax){
            for (i in 0..imax){
                normal[k++]=normalX[j][i]
                normal[k++]=normalY[j][i]
                normal[k++]=normalZ[j][i]
            }
        }
        normalBuffer.put(normal);
        normalBuffer.position(0);
    }
}