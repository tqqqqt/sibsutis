package com.example.mywave

import android.content.Context
import android.opengl.GLSurfaceView
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.viewinterop.AndroidView
import com.example.mywave.ui.theme.MyWaveTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            MyWaveTheme {
                MainWindow()
            }
        }
    }
}

class MyGlSurfaceView(context: Context): GLSurfaceView(context){
    private val renderer: MyGlRender

    init {
        setEGLContextClientVersion(2)
        renderer= MyGlRender(context)
        setRenderer(renderer)
        renderMode=GLSurfaceView.RENDERMODE_CONTINUOUSLY
    }
}

@Composable
fun MainWindow() {
    AndroidView(
        factory = { context -> MyGlSurfaceView(context).apply { } },
        modifier=Modifier.fillMaxSize()
    )
}
