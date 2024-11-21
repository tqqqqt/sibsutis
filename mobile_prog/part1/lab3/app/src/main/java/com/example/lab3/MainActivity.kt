package com.example.lab3

import android.media.MediaPlayer
import android.os.Bundle
import android.view.SoundEffectConstants
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.Canvas
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.gestures.detectTapGestures
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.MutableIntState
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.ImageBitmap
import androidx.compose.ui.input.pointer.pointerInput
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.LocalView
import androidx.compose.ui.res.imageResource
import androidx.compose.ui.unit.IntOffset
import androidx.compose.ui.unit.IntSize
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.lab3.ui.theme.Lab3Theme
import kotlinx.coroutines.*

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            Lab3Theme {
                val curentScreen = remember { mutableIntStateOf(1) }
                val gameScore = remember { mutableIntStateOf(0) }
                Box(
                    modifier = Modifier
                        .fillMaxSize()
                        .background(Color.Black)
                ) {
                    when (curentScreen.intValue) {
                        1 -> MainScreen(curentScreen)
                        2 -> GameScreen(curentScreen, gameScore)
                        3 -> EndGameScreen(curentScreen, gameScore)
                    }
                }
            }
        }
    }

    private suspend fun TimerText(textTimer: (String) -> Unit) {
        withContext(Dispatchers.Default) {
            var min: Int = 1
            var sec: Int = 30
            var tempText = ""
            while (true) {
                if (sec == 0) {
                    min -= 1;
                    sec = 59;
                    if (min < 0) break
                }
                sec -= 1
                if (sec >= 10) tempText = "$min:$sec"
                else tempText = "$min:0$sec"
                textTimer(tempText)
                delay(1000)
            }
        }
    }

    data class ShykResult(val numEnem: Int, var naprav:Int, var newX: Int, var newY: Int)
    data class TupPoint(var tapX: Float, var tapY: Float)

    @Composable
    private fun GameScreen(page: MutableIntState, gameScore: MutableIntState, ) {
        val textTimer = remember { mutableStateOf("1:30") }
        val shykColect = remember { mutableListOf<ShykResult>() }
        var ttemp = ShykResult(0,0,0,0)
        val tapPoint = TupPoint(0f, 0f)
        val view = LocalView.current
        val missSound = MediaPlayer.create(LocalContext.current,R.raw.miss)
        LaunchedEffect(key1 = Unit, block = {
            TimerText { updateText -> textTimer.value = updateText }
            page.intValue = 3
        })
        LaunchedEffect(key1 = shykColect.size, block = {
            //for (i in 0..1) {
                GameLogic { updateShyk ->
                    shykColect.add(updateShyk)
                }
            for(i in 0..shykColect.size-1){
                DirectGo(shykColect[i])
                shykColect.add(ttemp)
                shykColect.removeAt(shykColect.size - 1)
            }
            //}
            //delay(400)
        })
        LaunchedEffect(key1 = shykColect.size, block = {
            for(i in 0..shykColect.size-1) {
                DirectGo(shykColect[i])
                shykColect.add(ttemp)
                shykColect.removeAt(shykColect.size - 1)
            }
        })
        Column(
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.Center
        ) {
            Row(
                modifier = Modifier.fillMaxWidth(),
                horizontalArrangement = Arrangement.Center,
                verticalAlignment = Alignment.CenterVertically
            ) {
                Column(horizontalAlignment = Alignment.CenterHorizontally) {
                    Text(
                        text = "Score: " + gameScore.intValue.toString() + " ",
                        color = Color.LightGray,
                        fontSize = 20.sp
                    )
                    Text(text = textTimer.value, color = Color.LightGray, fontSize = 20.sp)
                }
            }
            Column {
                val shyk1 = ImageBitmap.imageResource(R.drawable.shyk1)
                val shyk2 = ImageBitmap.imageResource(R.drawable.shyk2)
                val shyk3 = ImageBitmap.imageResource(R.drawable.shyk3)
                Canvas(modifier = Modifier
                    .background(Color.Black)
                    .fillMaxWidth()
                    .fillMaxHeight()
                    .pointerInput(true) {
                        detectTapGestures() { click ->
                            tapPoint.tapX = click.x
                            tapPoint.tapY = click.y
                            var temp = 0
                            for (i in 0..shykColect.size - 1) {
                                if ((shykColect[i].newX <= tapPoint.tapX && shykColect[i].newX + 100 >= tapPoint.tapX) && (shykColect[i].newY <= tapPoint.tapY && shykColect[i].newY + 100 >= tapPoint.tapY)) {
                                    when (shykColect[i].numEnem) {
                                        1 -> gameScore.intValue += 1
                                        2 -> gameScore.intValue += 2
                                        3 -> gameScore.intValue += 3
                                    }
                                    temp += 1;
                                    view.playSoundEffect(SoundEffectConstants.CLICK)
                                    shykColect.removeAt(i);
                                    break;
                                }
                            }
                            if (temp == 0) {
                                missSound.start()
                                gameScore.intValue -= 5
                            }
                        }
                    }, onDraw = {
                    for (i in 0..shykColect.size - 1) {
                        DirectGo(shykColect[i])
                        when (shykColect[i].numEnem) {
                            1 -> drawImage(
                                image = shyk1,
                                dstSize = IntSize(100, 100),
                                dstOffset = IntOffset(shykColect[i].newX, shykColect[i].newY)
                            )

                            2 -> drawImage(
                                image = shyk2,
                                dstSize = IntSize(100, 100),
                                dstOffset = IntOffset(shykColect[i].newX, shykColect[i].newY)
                            )

                            3 -> drawImage(
                                image = shyk3,
                                dstSize = IntSize(100, 100),
                                dstOffset = IntOffset(shykColect[i].newX, shykColect[i].newY)
                            )
                        }
                    }
                })
            }
        }
    }

    private fun DirectGo(tempShyk: ShykResult){
        val tempAdd=10
        when(tempShyk.naprav){
            1->tempShyk.newY+=tempAdd
            2->{tempShyk.newX+=tempAdd
                tempShyk.newY-=tempAdd}
            3->tempShyk.newX+=tempAdd
            4->{tempShyk.newX+=tempAdd
                tempShyk.newY+=tempAdd}
            5->tempShyk.newY+=tempAdd
            6->{tempShyk.newX-=tempAdd
                tempShyk.newY+=tempAdd}
            7->tempShyk.newX-=tempAdd
            8->{tempShyk.newX-=tempAdd
                tempShyk.newY-=tempAdd}
        }
    }

    private suspend fun GameLogic(res: (ShykResult) -> Unit) {
        val tempX = (0..1000).random()
        val tempY = (0..2000).random()
        val tempNum = (1..3).random()
        val tempNaprav = (1..8).random()
        val tempRes = ShykResult(tempNum, tempNaprav, tempX, tempY)
        res(tempRes)
    }

    @Composable
    fun EndGameScreen(page: MutableIntState, gameScore: MutableIntState) {
        Column(
            modifier = Modifier.fillMaxSize(),
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.Center
        ) {
            Text(text = "Your score: ${gameScore.intValue}", color = Color.White, fontSize = 40.sp)
            Button(onClick = {
                gameScore.intValue = 0
                page.intValue = 2
            }, colors = ButtonDefaults.buttonColors(Color.Black), modifier = Modifier.border(1.dp,Color.White)) {
                Text(text = "Restart game", color = Color.White, fontSize = 40.sp)
            }
        }
    }

    @Composable
    fun MainScreen(page: MutableIntState) {
        Column(
            modifier = Modifier.fillMaxSize(),
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.Center
        ) {
            Button(onClick = { page.intValue = 2 }, colors = ButtonDefaults.buttonColors(Color.Black), modifier = Modifier.border(1.dp,Color.White)) {
                Text(text = "Start play", color = Color.White, fontSize = 40.sp)
            }
        }
    }
}

