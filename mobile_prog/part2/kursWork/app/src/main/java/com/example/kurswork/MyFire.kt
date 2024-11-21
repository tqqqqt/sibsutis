package com.example.kurswork

import android.content.Context
import android.opengl.Matrix
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import java.nio.ShortBuffer

class MyFire {
    private var context:Context

    private var imax=2
    private var jmax=2
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
    var normalBuffer: FloatBuffer
    var indexBuffer: ShortBuffer

    var model_matrix:FloatArray

    constructor(_context: Context, x_coord:Float, y_coord:Float, z_coord:Float){
        context=_context

        model_matrix= FloatArray(16)
        Matrix.setIdentityM(model_matrix,0)
        Matrix.translateM(model_matrix,0,x_coord,y_coord,z_coord)

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
                index[k]=chain(j,i)
                k++
                index[k]=chain(j+1,i)
                k++
            }
            if(j<jmax-1){
                index[k]=chain(j+1,imax)
                k++
            }
            j++
            if(j<jmax){
                for(i in imax downTo 0){
                    index[k]=chain(j,i)
                    k++
                    index[k]=chain((j+1),i)
                    k++
                }
                if(j<jmax-1){
                    index[k]=chain((j+1),0)
                    k++
                }
                j++
            }
        }

        var bi= ByteBuffer.allocateDirect(sizeindex*2)
        bi.order(ByteOrder.nativeOrder())
        indexBuffer=bi.asShortBuffer()
        indexBuffer.put(index)
        indexBuffer.position(0)

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
                y[j][i]=0.02f*temp_cos
            }
        }
        var k=0
        for(j in 0..jmax){
            for(i in 0..imax){
                vertex[k]=x[i]
                k++
                vertex[k]=y[j][i]
                k++
                vertex[k]=z[j]
                k++
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
                normal[k]=normalX[j][i]
                k++
                normal[k]=normalY[j][i]
                k++
                normal[k]=normalZ[j][i]
                k++
            }
        }
        normalBuffer.put(normal);
        normalBuffer.position(0);
    }

    fun rotateFire(angle:Float, x_rotate:Float, y_rotate:Float, z_rotate:Float){
        Matrix.rotateM(model_matrix,0,angle,x_rotate,y_rotate,z_rotate)
    }
}