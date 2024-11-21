package com.example.tabslab

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.size
import androidx.compose.material3.Button
import androidx.compose.material3.Slider
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.unit.dp
import kotlin.math.floor

@Composable
fun TablePage(){
    /*for(j in 0..5){
        Row{
            for(i in 0..2){
                Button(onClick = { }) {
                    Text(text="Button [$i;$j]", fontSize = 12.sp)
                }
            }
        }
    }*/
    var temp = remember { mutableStateOf(0f) }
    //var newTemp:Float = 1f
    Row {
        Image(painter = painterResource(id = if(temp.value>=5f) R.drawable.solnishko else R.drawable.snezhinka), contentDescription = "picture", modifier=Modifier.size(40.dp))
        Column {
            Slider(value = temp.value, valueRange = 0f..10f, onValueChange = { temp.value = it})
            Text(text = temp.toString())
        }

    }
}