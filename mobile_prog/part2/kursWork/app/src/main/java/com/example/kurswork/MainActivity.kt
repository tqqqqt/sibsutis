package com.example.kurswork

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
import com.example.kurswork.ui.theme.KursWorkTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            KursWorkTheme {
                MainWindow()
            }
        }
    }
}

class MyGlSurface(_context: Context): GLSurfaceView(_context){
    private var renderer:MyRender

    init{
        setEGLContextClientVersion(2)
        renderer= MyRender(_context)
        setRenderer(renderer)
        renderMode=RENDERMODE_CONTINUOUSLY
    }
}

@Composable
fun MainWindow() {
    AndroidView(
        factory = { context -> MyGlSurface(context).apply { } },
        modifier = Modifier.fillMaxSize()
    )
}