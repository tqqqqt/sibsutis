package com.example.tabslab

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.Text
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.MutableIntState
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.sp
import androidx.compose.ui.unit.dp
import com.example.tabslab.ui.theme.TabslabTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            TabslabTheme {
                val textLists = rememberSaveable { mutableListOf<String>() }
                val curentPage = rememberSaveable { mutableIntStateOf(1) }
                CreateMainPage(curentPage, textLists)
            }
        }
    }

    @Composable
    private fun CreateMainPage(curentPage: MutableIntState, textLists: MutableList<String>){
        Box (modifier= Modifier
            .fillMaxSize()
            .background(Color.White)){
            Column {
                Row (modifier= Modifier
                    .fillMaxWidth()
                    .padding(bottom = 10.dp)
                    .background(Color.Blue)){
                    Button(onClick = { curentPage.intValue=1 }, modifier= Modifier
                        .weight(1f)
                        .background(Color.Blue),
                        colors = ButtonDefaults.buttonColors(Color.Blue)){
                        Text(text="Image",fontSize=25.sp,color=if(curentPage.intValue==1) Color.Cyan else Color.White)
                    }
                    Button(onClick = { curentPage.intValue=2 }, modifier= Modifier
                        .weight(1f)
                        .background(Color.Blue),
                        colors = ButtonDefaults.buttonColors(Color.Blue)){
                        Text(text="List",fontSize=25.sp,color=if(curentPage.intValue==2) Color.Cyan else Color.White)
                    }
                    Button(onClick = { curentPage.intValue=3 }, modifier= Modifier
                        .weight(1f)
                        .background(Color.Blue),
                        colors = ButtonDefaults.buttonColors(Color.Blue)){
                        Text(text="Tabs",fontSize=25.sp,color=if(curentPage.intValue==3) Color.Cyan else Color.White)
                    }
                }
                Column {
                    TabsContent(curentPage.intValue, textLists)
                }
            }
        }
    }

    @Composable
    private fun TabsContent(numTabs:Int, textLists: MutableList<String>){
        when(numTabs){
            1 -> ImagePage()
            2 -> ListPage(textLists)
            3 -> TablePage()
            else -> { }
        }
    }
}