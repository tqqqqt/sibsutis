package com.example.mywidgetl6

import android.content.Context
import androidx.compose.runtime.Composable
import androidx.compose.runtime.MutableIntState
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.sp
import androidx.glance.Button
import androidx.glance.GlanceId
import androidx.glance.GlanceModifier
import androidx.glance.LocalContext
import androidx.glance.action.actionStartActivity
import androidx.glance.action.clickable
import androidx.glance.layout.Column
import androidx.glance.appwidget.GlanceAppWidget
import androidx.glance.appwidget.GlanceAppWidgetReceiver
import androidx.glance.appwidget.provideContent
import androidx.glance.layout.Alignment
import androidx.glance.layout.Row
import androidx.glance.layout.fillMaxSize
import androidx.glance.text.FontWeight
import androidx.glance.text.Text
import androidx.glance.text.TextStyle
import androidx.glance.unit.ColorProvider

class MyWidget : GlanceAppWidget() {

    private fun ChangeInfo(context: Context, tempString: MutableState<String>, curentInfo: MutableIntState){
        val tempPref=context.getSharedPreferences("myPref",0)
        val newString=tempPref.getString("widgetInfo${curentInfo.intValue}","||").toString()
        if(newString=="||") tempString.value="Неизвестно"
        else tempString.value=newString
    }

    private fun UpdateInfo(context: Context, curProcess:MutableIntState, tempString:MutableState<String>, curentInfo:MutableIntState){
        curProcess.intValue = 1
        val tempPref=context.getSharedPreferences("myPref",0)
        val newString=tempPref.getString("widgetInfo${curentInfo.intValue}","||").toString()
        if(newString=="||"){
            tempString.value="Неизвестно"
        }
        else{
            tempString.value=newString
        }
        curProcess.intValue=0
    }

    @Composable
    fun Content() {
        val tempString = remember { mutableStateOf("") }
        val curentProcess = remember { mutableIntStateOf(0) }
        val curentInfo = remember { mutableIntStateOf(0) }
        val context= LocalContext.current
        Column(
            modifier = GlanceModifier.fillMaxSize()
                .clickable(actionStartActivity(MainActivity::class.java)),
            verticalAlignment = Alignment.CenterVertically,
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            Text(
                text = tempString.value, style = TextStyle(
                    fontWeight = FontWeight.Medium,
                    color = ColorProvider(Color.White),
                    fontSize = 20.sp
                )
            )
            Column (
                horizontalAlignment = Alignment.CenterHorizontally,
                verticalAlignment = Alignment.Bottom) {
                Row(
                    horizontalAlignment = Alignment.CenterHorizontally,
                    verticalAlignment = Alignment.Bottom
                ) {
                    Button(text = "Назад", onClick = {
                        curentInfo.intValue-=1
                        if(curentInfo.intValue<0) curentInfo.intValue=3
                        ChangeInfo(context,tempString,curentInfo)
                    })
                    Button(text = "Вперед", onClick = {
                        curentInfo.intValue+=1
                        if(curentInfo.intValue>=4) curentInfo.intValue=0
                        UpdateInfo(context,curentProcess,tempString,curentInfo)
                    })
                }
                Button(text = if(curentProcess.intValue==0) "Обновить" else "В процессе", onClick = {
                    curentInfo.intValue=0
                    UpdateInfo(context,curentProcess,tempString,curentInfo)
                })
            }
        }
    }

    override suspend fun provideGlance(context: Context, id: GlanceId) {
        provideContent {
            Content()
        }
    }
}

class WidgetReceiver : GlanceAppWidgetReceiver() {
    override val glanceAppWidget: GlanceAppWidget
        get() = MyWidget()
}