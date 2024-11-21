package com.example.astronomicalhandbook

import android.content.Context
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.util.Log
import android.view.MotionEvent
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.size
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Favorite
import androidx.compose.material3.Button
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.MutableIntState
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clipToBounds
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp
import androidx.compose.ui.viewinterop.AndroidView
import androidx.compose.ui.zIndex
import com.example.astronomicalhandbook.ui.theme.AstronomicalHandbookTheme
import kotlinx.coroutines.delay


class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            AstronomicalHandbookTheme {
                ShowWindow()
            }
        }
    }
}

class NewsElement(new_title: String, new_text: String, first_number: Int) {
    var main_title = mutableStateOf(new_title)
    var text_news = mutableStateOf(new_text)
    var number_like = mutableIntStateOf(first_number)
}

class MyGlSurfaceView(context: Context): GLSurfaceView(context){
    private val renderer: MyGlRender

    init {
        setEGLContextClientVersion(1)
        renderer=MyGlRender(context)
        setRenderer(renderer)
        this.renderMode=RENDERMODE_CONTINUOUSLY
    }

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        renderer.clickScreen(event!!.getX()/width,event!!.getY()/height)
        return super.onTouchEvent(event)
    }


}

@Composable
fun ShowWindow(){
    val curent_window = rememberSaveable {
        mutableIntStateOf(1)
    }
    if(curent_window.intValue==1){
        val news_colection = remember { mutableStateListOf<NewsElement>() }
        val avalible_news = remember { mutableStateListOf<Int>() }
        val curent_news = remember { mutableStateListOf<Int>()}
        if(news_colection.size==0 && avalible_news.size==0) {
            LoadNews(news_colection, avalible_news)
            for (i in 0..3) {
                curent_news.add(avalible_news[(0..<avalible_news.size).random()])
                avalible_news.remove(curent_news.last())
            }
        }
        NewsWindow(curent_window, news_colection, avalible_news, curent_news)
    }
    else if(curent_window.intValue==2) MainProgWindow()
}

fun LoadNews(news_colection: MutableList<NewsElement>, avalible_news: MutableList<Int>){
    news_colection.add(NewsElement("Update info", "Create project and start write interface.", (1..10).random()))
    news_colection.add(NewsElement("Patch #2", "- Delete old interface.\n- Fix more 200 bugs.", (1..10).random()))
    news_colection.add(NewsElement("World news", "The sun rose in the north. The moon is still in the sky.", (1..10).random()))
    news_colection.add(NewsElement("Tech news", "A new iPhone was shown. It is extremely expensive.", (1..10).random()))
    news_colection.add(NewsElement("Question", "What brand of car do you prefer? Why?", (1..10).random()))
    news_colection.add(NewsElement("Recommend app", "Recommend our application to more users so that we want to improve it",(1..10).random()))
    news_colection.add(NewsElement("Patch #3", "- Changed the appearance of news.\n- Added the function of rating news.", (1..10).random()))
    news_colection.add(NewsElement("Project info", "This app is an astronomical reference book. Someday it will be fully completed.", (1..10).random()))
    news_colection.add(NewsElement("Fact", "The sun is shining in the morning and it's time to go to work.", (1..10).random()))
    news_colection.add(NewsElement("Future updates", "We need to create functionality for the main screen, we need to add graphics to it, fill out the directory.", (1..10).random()))
    for(i in 0..<news_colection.size) avalible_news.add(i)
}

@Composable
fun NewsWindow(curent_window: MutableIntState, news_colection: MutableList<NewsElement>, avalible_news: MutableList<Int>, curent_news: MutableList<Int>) {
    LaunchedEffect(Unit){
        repeat(4) {
            val cur_index=(0..3).random()
            val save_index_news=curent_news[cur_index]
            curent_news[cur_index]=avalible_news[(0..<avalible_news.size).random()]
            avalible_news.remove(curent_news[cur_index])
            avalible_news.add(save_index_news)
            delay(500)
        }
        curent_window.intValue=2
    }
    Column(
        modifier = Modifier
            .fillMaxHeight()
            .fillMaxWidth()
    ) {
        Row(modifier = Modifier.fillMaxWidth()) {
            ShowNewsElement(news_colection[curent_news[0]], 0.5f, 0.5f)
            ShowNewsElement(news_colection[curent_news[1]], 0.5f, 1f)
        }
        Row(modifier = Modifier.fillMaxWidth()) {
            ShowNewsElement(news_colection[curent_news[2]], 1f, 0.5f)
            ShowNewsElement(news_colection[curent_news[3]], 1f, 1f)
        }

    }
}

@Composable
fun ShowNewsElement(temp_element: NewsElement, control_height: Float, control_width: Float) {
    Column (modifier= Modifier
        .fillMaxWidth(control_width)
        .fillMaxHeight(control_height)
        .border(1.dp, Color.Black)) {
        Text(text = temp_element.main_title.value, modifier= Modifier
            .fillMaxWidth()
            .fillMaxHeight(0.1f))
        Text(text=temp_element.text_news.value, modifier= Modifier
            .fillMaxWidth()
            .fillMaxHeight(0.8f))
        Row {
            IconButton(onClick = { temp_element.number_like.intValue++ }) {
                Icon(Icons.Filled.Favorite, contentDescription = "like", modifier=Modifier.size(60.dp))
            }
            Text(text="${temp_element.number_like.intValue}")
        }
    }
}

@Composable
fun MainProgWindow(){
    AndroidView(
        factory = { context -> MyGlSurfaceView(context).apply {  } },
        modifier = Modifier.fillMaxSize()
    )
}
